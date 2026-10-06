// game_state.c
#include "game_state.h"

const char *get_location_name(LocationID location)
{
  switch (location)
  {
  case LOCATION_OUTSIDE:
    return "Outside";
  case LOCATION_ELEVATOR:
    return "Elevator";
  case LOCATION_LOBBY:
    return "Lobby";
  case LOCATION_KITCHEN:
    return "Kitchen";
  case LOCATION_LIVING_ROOM:
    return "Living Room";
  case LOCATION_BEDROOM:
    return "Bedroom";
  case LOCATION_BATHROOM:
    return "Bathroom";
  case LOCATION_BALCONY:
    return "Balcony";
  default:
    return "Unknown";
  }
}