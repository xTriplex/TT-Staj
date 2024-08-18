#include <amxmodx>
#include <fakemeta>
#include <fun>

new g_num_players = 0;

public plugin_init()
{
    register_event("ResetHUD", "check_player_count", "a"); // Check player count when players spawn or respawn
    register_event("DeathMsg", "player_death", "a");       // Check player count when a player dies
    register_event("TeamInfo", "team_change", "a");        // Check player count when a player changes teams
    register_event("PlayerSpawn", "player_spawn", "b");    // Check player count when a player spawns
    register_clcmd("say /check", "cmd_check");             // Optional command to manually check player count
}

public check_player_count()
{
    new max_players = get_maxplayers();
    g_num_players = 0;

    for (new i = 1; i <= max_players; i++)
    {
        if (is_user_connected(i) && is_user_alive(i))
        {
            g_num_players++;
        }
    }

    client_print(0, print_chat, "[DEBUG] Current active players: %d", g_num_players);

    if (g_num_players == 2)
    {
        client_print(0, print_chat, "[DEBUG] 1v1 match detected. Disabling footsteps.");
        disable_footsteps();
    }
    else
    {
        client_print(0, print_chat, "[DEBUG] Not a 1v1 match. Enabling footsteps.");
        enable_footsteps();
    }
}

public disable_footsteps()
{
    server_cmd("mp_footsteps 0");
    client_print(0, print_chat, "[DEBUG] Footsteps disabled.");
}

public enable_footsteps()
{
    server_cmd("mp_footsteps 1");
    client_print(0, print_chat, "[DEBUG] Footsteps enabled.");
}

// Optional command to manually check player count
public cmd_check(id)
{
    check_player_count();
    client_print(id, print_chat, "[DEBUG] Checked player count and adjusted footsteps.");
}

// Event handlers to update player count dynamically
public player_death()
{
    check_player_count();
}

public team_change()
{
    check_player_count();
}

public player_spawn()
{
    check_player_count();
}
