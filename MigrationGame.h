#include "MigrationData.h"

#ifndef IFDEBUG
#define IFDEBUG(...) ((void)((DEBUG_LEVEL) && (__VA_ARGS__, 0)))
#define DEBUG_LEVEL 1 // set to 1 to compile in Serial Debug prints
#endif

#ifndef PRINTEX_VERSION
#include <PrintEx.h>
#endif

#ifndef MigrationGame_h
#define MigrationGame_h

typedef enum  {
  NO_PLANT_SELECTED,
  NO_PLANT_PRIMED,
  PLANT_INTIALLY_SELECTED,
  PLANT_INTIALLY_DIMMING,
  PLANT_INTIALLY_DIMMING_FINISHED,
  PLANT_ACCEPTED_WAITING_FOR_BUTTON,
  INCORRECT_REGION_SELECTED,
  INCORRECT_REGION_WAIT_TO_TURN_OFF,
  CORRECT_REGION_SELECTED,
  CORRECT_REGION_WAIT_TO_TURN_OFF,
  START_DRAWING_LINE_TO_REGION,
  DRAWING_LINE_TO_REGION,
  START_DRAWING_SEGMENT,
  LOOP_EACH_LED,
  FINISHED_SEGMENT,
  FINISHED_LINE_TO_REGION,
  WINNER_START,
  WINNER_END,
  ABANDONED
  } state_m; //enum state_m

static const char stateStr[][35] PROGMEM = {
  "NO_PLANT_SELECTED",
  "NO_PLANT_PRIMED",
  "PLANT_INTIALLY_SELECTED",
  "PLANT_INTIALLY_DIMMING",
  "PLANT_INTIALLY_DIMMING_FINISHED",
  "PLANT_ACCEPTED_WAITING_FOR_BUTTON",
  "INCORRECT_REGION_SELECTED",
  "INCORRECT_REGION_WAIT_TO_TURN_OFF",
  "CORRECT_REGION_SELECTED",
  "CORRECT_REGION_WAIT_TO_TURN_OFF",
  "START_DRAWING_LINE_TO_REGION",
  "DRAWING_LINE_TO_REGION",
  "START_DRAWING_SEGMENT",
  "LOOP_EACH_LED",
  "FINISHED_SEGMENT",
  "FINISHED_LINE_TO_REGION",
  "WINNER_START",
  "WINNER_END",
  "ABANDONED"
};

class MigrationGame {
  private:

    //Stream* _serial;
    StreamEx* _serial;
    
  public:

    typedef struct {
      int plant[4];  // current Plant is index 0
      int hopPos;
      int stepPos;
      int region[4]; // index 0 is buffered, index 1 will be current.
    } History;

    bool reverse;
    int ledSegPos;
    int ledpos;
    int startPos;
    int endPos;
    int currentBrightness;
    uint32_t ledNextMillis;
    uint32_t ledStartMillis;
    uint32_t ledDelayMillis;

    History history;
    state_m gameState[10];
  
    MigrationGame();
    ~MigrationGame();
    void begin();
    void begin(Stream &serial);
    int  lookforRegion(String *consoleInputStr);
    int  lookforPlant(int consoleInputNumber);
    void printPlantWithLED();
    void printRegionHistory();
    void printPlantHistory();
    void printGameStateHistory();
    void printPlants();
    void printRegions();
    bool updatePlant(int newPlant);
    void updateRegion(int newRegion);
    void updateGameState(state_m newState);
    int  printCurrentDesiredRegion();
    bool checkIfMatchCurrentDesiredRegions(int nextRegionIdx);
    bool checkIfAtEndOfRegions();
    // bool checkUpdateHop(int newHop);
    // int  MigrationGame::checkIfMatchCurrentDesiredRegions(int nextRegionIdx);
};

#endif  // MigrationGame_h
