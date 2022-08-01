package org.torproject.android

import android.annotation.SuppressLint
import android.content.BroadcastReceiver
import android.content.Context
import android.content.Intent
import android.content.IntentFilter
import android.content.res.ColorStateList
import android.net.VpnService
import android.os.Build
import android.os.Bundle
import android.text.Spannable
import android.text.SpannableString
import android.text.style.TextAppearanceSpan
import android.view.Gravity
import android.view.MenuItem
import android.view.View
import android.widget.*
import androidx.appcompat.app.ActionBarDrawerToggle
import androidx.appcompat.app.AppCompatActivity
import androidx.constraintlayout.widget.Group
import androidx.core.content.ContextCompat
import androidx.core.view.forEach
import androidx.drawerlayout.widget.DrawerLayout
import androidx.localbroadcastmanager.content.LocalBroadcastManager
import com.google.android.material.navigation.NavigationView
import net.freehaven.tor.control.TorControlCommands
import org.torproject.android.core.LocaleHelper
import org.torproject.android.core.ui.SettingsPreferencesActivity
import org.torproject.android.service.OrbotConstants
import org.torproject.android.service.OrbotService
import org.torproject.android.service.util.Prefs
import org.torproject.android.ui.AppManagerActivity
import org.torproject.android.ui.OrbotMenuAction
import org.torproject.android.ui.dialog.AboutDialogFragment
import org.torproject.android.ui.v3onionservice.OnionServiceActivity
import org.torproject.android.ui.v3onionservice.PermissionManager
import org.torproject.android.ui.v3onionservice.clientauth.ClientAuthActivity
import java.util.*

class OrbotActivity : AppCompatActivity(), ExitNodeDialogFragment.ExitNodeSelectedCallback {

    // main screen UI
    private lateinit var tvTitle: TextView
    private lateinit var tvSubtitle: TextView
    private lateinit var tvConfigure: TextView
    private lateinit var btnStartVpn: Button
    private lateinit var ivOnion: ImageView
    private lateinit var progressBar: ProgressBar
    private lateinit var lvConnectedActions: ListView
    private lateinit var tvVolunteer: TextView
    private lateinit var tvVolunteerSubtitle: TextView
    // menu UI
    private lateinit var drawerLayout: DrawerLayout
    private lateinit var menuToggle: ActionBarDrawerToggle
    private lateinit var navigationView: NavigationView
    private lateinit var tvPorts: TextView
    private lateinit var torStatsGroup: Group

    private var previousReceivedTorStatus: String? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_orbot)
        tvTitle = findViewById(R.id.tvTitle)
        tvSubtitle = findViewById(R.id.tvSubtitle)
        tvConfigure = findViewById(R.id.tvConfigure)
        btnStartVpn = findViewById(R.id.btnStart)
        ivOnion = findViewById(R.id.ivStatus)
        progressBar = findViewById(R.id.progressBar)
        lvConnectedActions = findViewById(R.id.lvConnected)
        val listItems = arrayListOf(OrbotMenuAction(R.string.btn_change_exit, 0) {openExitNodeDialog()},
            OrbotMenuAction(R.string.btn_refresh, R.drawable.ic_refresh) {sendNewnymSignal()},
            OrbotMenuAction(R.string.btn_tor_off, R.drawable.ic_power) {stopTorAndVpn()})

        if (CAN_DO_APP_ROUTING) listItems.add(0, OrbotMenuAction(R.string.btn_choose_apps, R.drawable.ic_choose_apps) {
            startActivityForResult(Intent(this, AppManagerActivity::class.java), REQUEST_VPN_APP_SELECT)
        })
        lvConnectedActions.adapter = OrbotMenuActionAdapter(this, listItems)
        tvVolunteer = findViewById(R.id.tvVolunteerMode)
        tvVolunteerSubtitle = findViewById(R.id.tvVolunteerSubtitle)
        drawerLayout = findViewById(R.id.drawerLayout)
        navigationView = findViewById(R.id.navigationView)
        configureNavigationMenu()
        menuToggle = ActionBarDrawerToggle(this, drawerLayout, R.string.drawer_open, R.string.drawer_close)
        drawerLayout.addDrawerListener(menuToggle)
        menuToggle.syncState()
        supportActionBar?.setDisplayHomeAsUpEnabled(true)
        tvVolunteer.setOnClickListener {openVolunteerMode()}
        tvVolunteerSubtitle.setOnClickListener {openVolunteerMode()}
        tvConfigure.setOnClickListener {openConfigureTorConnection()}

        doLayoutOff()

        with(LocalBroadcastManager.getInstance(this)) {
            registerReceiver(orbotServiceBroadcastReceiver, IntentFilter(OrbotConstants.LOCAL_ACTION_STATUS))
            registerReceiver(orbotServiceBroadcastReceiver, IntentFilter(OrbotConstants.LOCAL_ACTION_LOG))
            registerReceiver(orbotServiceBroadcastReceiver, IntentFilter(OrbotConstants.LOCAL_ACTION_PORTS))
        }
    }

    private fun openExitNodeDialog() {
        ExitNodeDialogFragment(this).show(supportFragmentManager, "foo")
    }

    private fun configureNavigationMenu() {
        navigationView.getHeaderView(0).let {
            tvPorts = it.findViewById(R.id.tvPorts)
            torStatsGroup = it.findViewById(R.id.torStatsGroup)
        }
        // apply theme to colorize menu headers
        navigationView.menu.forEach { menu -> menu.subMenu?.let { // if it has a submenu, we want to color it
            menu.title = SpannableString(menu.title).apply {
                setSpan(TextAppearanceSpan(this@OrbotActivity, R.style.NavigationGroupMenuHeaders), 0, this.length, 0)
            }
        } }
        // set click listeners for menu items
        navigationView.setNavigationItemSelectedListener {
            when (it.itemId) {
                R.id.menu_tor_connection -> openConfigureTorConnection()
                R.id.menu_help_others -> openVolunteerMode()
                R.id.menu_v3_onion_services -> startActivity(Intent(this, OnionServiceActivity::class.java))
                R.id.menu_v3_onion_client_auth -> startActivity(Intent(this, ClientAuthActivity::class.java))
                R.id.menu_settings -> startActivityForResult(SettingsPreferencesActivity.createIntent(this, R.xml.preferences), REQUEST_CODE_SETTINGS)
                R.id.menu_faq -> Toast.makeText(this, "TODO FAQ not implemented...", Toast.LENGTH_LONG).show()
                R.id.menu_about -> {
                    AboutDialogFragment().show(supportFragmentManager, AboutDialogFragment.TAG)
                    drawerLayout.closeDrawer(Gravity.LEFT)
                }
                else -> {}
            }
            true
        }
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean =
        menuToggle.onOptionsItemSelected(item) || super.onOptionsItemSelected(item)

    override fun onResume() {
        super.onResume()
        sendIntentToService(OrbotConstants.CMD_ACTIVE)
    }

    override fun onDestroy() {
        super.onDestroy()
        LocalBroadcastManager.getInstance(this).unregisterReceiver(orbotServiceBroadcastReceiver)
    }

    private fun sendIntentToService(intent: Intent) = ContextCompat.startForegroundService(this, intent)
    private fun sendIntentToService(action: String) = sendIntentToService(Intent(this, OrbotService::class.java).apply {
        this.action = action
    })

    private fun startTorAndVpn() {
        val vpnIntent = VpnService.prepare(this)
        if (vpnIntent != null) {
            startActivityForResult(vpnIntent, REQUEST_CODE_VPN)
        } else {
            // todo probably just remove this pref altogether and always start VPN
            Prefs.putUseVpn(true)
            sendIntentToService(OrbotConstants.ACTION_START)
            sendIntentToService(OrbotConstants.ACTION_START_VPN)
        }
    }

    private fun stopTorAndVpn() {
        sendIntentToService(OrbotConstants.ACTION_STOP)
        sendIntentToService(OrbotConstants.ACTION_STOP_VPN)
    }

    private fun sendNewnymSignal() {
        sendIntentToService(TorControlCommands.SIGNAL_NEWNYM)
    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)
        if (requestCode == REQUEST_CODE_VPN && resultCode == RESULT_OK) {
            startTorAndVpn()
        } else if (requestCode == REQUEST_CODE_SETTINGS && resultCode == RESULT_OK) {
            // todo respond to language change extra data here...
        } else if (requestCode == REQUEST_VPN_APP_SELECT && resultCode == RESULT_OK) {
            sendIntentToService(OrbotConstants.ACTION_RESTART_VPN) // is this enough todo?
        }
    }

    override fun attachBaseContext(newBase: Context) = super.attachBaseContext(LocaleHelper.onAttach(newBase))

    private val orbotServiceBroadcastReceiver = object : BroadcastReceiver(){
        @SuppressLint("SetTextI18n")
        override fun onReceive(context: Context?, intent: Intent?) {
            val status = intent?.getStringExtra(OrbotConstants.EXTRA_STATUS)
            when (intent?.action) {
                OrbotConstants.LOCAL_ACTION_STATUS -> {
                    if (status.equals(previousReceivedTorStatus)) return
                    previousReceivedTorStatus = status
                    when (status) {
                        OrbotConstants.STATUS_OFF -> doLayoutOff()
                        OrbotConstants.STATUS_STARTING -> doLayoutStarting()
                        OrbotConstants.STATUS_ON -> doLayoutOn()
                        OrbotConstants.STATUS_STOPPING -> {}
                    }
                }
                OrbotConstants.LOCAL_ACTION_LOG -> {
                    intent.getStringExtra(OrbotConstants.LOCAL_EXTRA_BOOTSTRAP_PERCENT)?.let {
                        progressBar.progress = Integer.parseInt(it)
                    }
                }
                OrbotConstants.LOCAL_ACTION_PORTS -> {
                    val socks = intent.getIntExtra(OrbotConstants.EXTRA_SOCKS_PROXY_PORT, -1)
                    val http = intent.getIntExtra(OrbotConstants.EXTRA_HTTP_PROXY_PORT, -1)
                    if (http > 0 && socks > 0) tvPorts.text = "SOCKS $socks | HTTP $http"
                }
                else -> {}
            }
        }
    }

    private fun doLayoutOff() {
        ivOnion.setImageResource(R.drawable.ic_disconnected)
        tvSubtitle.visibility = View.VISIBLE
        progressBar.visibility = View.INVISIBLE
        lvConnectedActions.visibility = View.GONE
        tvTitle.text = getString(R.string.secure_your_connection_title)
        tvConfigure.visibility = View.VISIBLE
        torStatsGroup.visibility = View.GONE
        tvPorts.text = getString(R.string.ports_not_set)
        with(btnStartVpn) {
            visibility = View.VISIBLE
            text = getString(R.string.btn_start_vpn)
            isEnabled = true
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
                backgroundTintList = ColorStateList.valueOf(
                    ContextCompat.getColor(
                        this@OrbotActivity,
                        R.color.orbot_btn_enabled_purple
                    )
                )
            }
            setOnClickListener { startTorAndVpn() }
        }
    }

    private fun doLayoutOn() {
        ivOnion.setImageResource(R.drawable.ic_connected)
        tvSubtitle.visibility = View.GONE
        progressBar.visibility = View.INVISIBLE
        tvTitle.text = getString(R.string.connected_title)
        tvSubtitle.visibility = View.GONE
        btnStartVpn.visibility = View.GONE
        lvConnectedActions.visibility = View.VISIBLE
        tvConfigure.visibility = View.GONE
    }

    private fun doLayoutStarting() {
        torStatsGroup.visibility = View.VISIBLE
        tvSubtitle.visibility = View.VISIBLE
        with(progressBar) {
            progress = 0
            visibility = View.VISIBLE
        }
        tvTitle.text = getString(R.string.trying_to_connect_title)
        with(btnStartVpn) {
            text = getString(android.R.string.cancel)
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
                backgroundTintList = ColorStateList.valueOf(
                    ContextCompat.getColor(
                        this@OrbotActivity,
                        R.color.orbot_btn_disable_grey
                    )
                )
            }
            setOnClickListener { stopTorAndVpn() }
        }
    }

    // todo not really defined what this does, somehow start/manage being a snowflake proxy
    private fun openVolunteerMode() {
        Toast.makeText(this, "Volunteer Mode Not Implemented...", Toast.LENGTH_LONG).show()
    }

    // todo not really defined yet
    private fun openConfigureTorConnection() {
        startActivity(Intent(this, TestConnectionActivity::class.java))
    }


    companion object {
        const val REQUEST_CODE_VPN = 1234
        const val REQUEST_CODE_SETTINGS = 2345
        const val REQUEST_VPN_APP_SELECT = 2432
        private val CAN_DO_APP_ROUTING = PermissionManager.isLollipopOrHigher()
    }

    override fun onExitNodeSelected(exitNode: String, countryDisplayName: String) {
        sendIntentToService(
            Intent(this, OrbotService::class.java)
                .setAction(OrbotConstants.CMD_SET_EXIT)
                .putExtra("exit", exitNode)
        )

    }

}