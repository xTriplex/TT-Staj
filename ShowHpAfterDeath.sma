#include <amxmodx>
#include <fakemeta>
#include <hamsandwich>

// HUD sync object
new g_hudmsg;

// Initialize plugin
public plugin_init()
{
    register_plugin("Killer HP Display", "1.0", "xTriplex");

    // Register event for player death
    register_event("DeathMsg", "event_death", "a");

    // Create HUD sync object for displaying HP
    g_hudmsg = CreateHudSyncObj();
}

// Handle player death event
public event_death()
{
    new victim = read_data(2);
    new attacker = get_user_attacker(victim);

    // Ensure valid attacker and victim indices
    if (attacker > 0 && attacker <= 32 && victim > 0 && victim <= 32 && attacker != victim)
    {
        // Get the killer's name
        static killer_name[32];
        get_user_name(attacker, killer_name, sizeof(killer_name));

        // Get the killer's remaining HP
        new killer_hp = get_user_health(attacker);

        // Display killer's remaining HP to the victim using HUD message
        set_hudmessage(255, 255, 0, 0.45, 0.50, 2, 1.0, 12.0, 0.1, 0.1, -1);
        ShowSyncHudMsg(victim, g_hudmsg, "%s has %d HP left.", killer_name, killer_hp);
    }
}
