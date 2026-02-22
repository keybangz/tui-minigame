#include <stdio.h>
#include <unistd.h> // For sleep
#include <stdint.h>
#include <time.h>
#include <ncurses.h> // For TUI framework ncurses

/*
 * NCurses TUI Game
 * Goal: Create simple League of Legends like laning phase mini-game
 * 
 * TODO:
     - Refactor current code outside of main file.
     - Add functionality in different files e.g. control binding, UI control, framerate control, main core loop control
     - Create UI framework helper functions for drawing different sized windows for different usages on screen (main menu, in-game, etc)
     - Add mouse input
     
 * Thanks to https://github.com/dunamismax/c-from-the-ground-up for simple implementation demonstration of ncurses.
 */

typedef struct gameState{
    int running;
    int testCount;
    int keyPressed;
} gameState;

// UI
void draw_ui(void);

// Game functionality
void refreshFrame(WINDOW*);
void setupFrame(gameState*);
struct timespec timespec_sub(struct timespec, struct timespec);

// Game mechanics
int mapKeyPress(gameState*);
void mapActionToKey(gameState*);

// Memory management
void init(void);
void cleanup(void);

int main(int argc, char* argv[]) {
    if(argc > 1) {
        printf("Usage: %s\n", argv[0]);
        return 1;
    }

    gameState state;
    state.testCount = 0;
    
    init(); // Init
    draw_ui(); // Draw the ui written.
    state.running = 1;

    setupFrame(&state);

    cleanup(); // Cleanup memory from ncurses
    return 0;
}

/*
- UI functionality
*/
void draw_ui() {
    clear(); // Clear virtual screen
    
    // 0,0 is top left corner of screen
    mvprintw(0, 0, "Test print on interface environment");
    
    // attron - Turn attribute on
    attron(COLOR_PAIR(1) | A_BOLD); // Turn the pair defined in init() and make text bold.
    mvprintw(2, 2, "Test yellow bold text on black bg");
    attroff(COLOR_PAIR(1) | A_BOLD); // attroff, turn selected attributes off.
    
    mvprintw(4, 2, "Standard text again.");
    
    refreshFrame(NULL); // Wrapper function for refresh() & wrefresh()
    
    // Refactor later.
    int height = 10, width = 60;
    int start_y = 6, start_x = 5;
    
    // newwin creates a window inside the virtual screen
    WINDOW* info_win = newwin(height, width, start_y, start_x);
    
    // Draw border around the window
    box(info_win, 0, 0);
    
    // Attribute for window color only
    wbkgd(info_win, COLOR_PAIR(3));
    
    // mvwprintw is the window specific function of mvprintw
    // Coordinates are relative to top left of new window, just like virtual screen.
    mvwprintw(info_win, 1, 1, "New window test.");
    
    // Modular refreshment of window only.
    refreshFrame(info_win);
}

/*
- Core game functionality
*/
void setupFrame(gameState* state) {
    if(!state)
        return;
    
    // REF: https://www.altdevarts.com/p/a-simple-main-game-loop-with-ncurses
    struct timespec frame_time;
    struct timespec remaining_time;
    struct timespec target_time = { 0, 16666666 };
    
    while(state->running) {
        timeout(0);    
        state->keyPressed = getch();
        
        struct timespec start_time;
        clock_gettime(CLOCK_REALTIME, &start_time);
        
        refreshFrame(NULL);
        
        mvprintw(6, 2, "Count: %d", state->testCount);
        state->testCount++;
        
        struct timespec end_time;
        clock_gettime(CLOCK_REALTIME, &end_time);
        
        frame_time = timespec_sub(start_time, end_time);
        remaining_time = timespec_sub(frame_time, target_time);
        
        nanosleep(&remaining_time, NULL);
        
        if(!state->running || state->keyPressed == KEY_BACKSPACE)
            break;
    }
}

int mapKeyPress(gameState* state) {
    if(!state)
        return -1;
    
    return state->keyPressed;
}

void mapActionToKey(gameState* state) {
    if(!state)
        return;
    
}

void refreshFrame(WINDOW* window) {
    if(window) {
        wrefresh(window);
    } else
        refresh();
}

// REF: https://www.altdevarts.com/p/a-simple-main-game-loop-with-ncurses
// https://sourceware.org/glibc/manual/2.34/html_node/Calculating-Elapsed-Time.html
struct timespec timespec_sub(struct timespec start, struct timespec end) {
    struct timespec temp;
    
    if ((end.tv_nsec-start.tv_nsec)<0) {
        temp.tv_sec  = end.tv_sec-start.tv_sec-1;
        temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
    } else {
        temp.tv_sec  = end.tv_sec-start.tv_sec;
        temp.tv_nsec = end.tv_nsec-start.tv_nsec;
    }
    
    return temp;
}

/*
- Ncurses core functions
*/
void init(void) {
    initscr(); // NCurses initialize screen function.
    noecho(); // Prevents keypresses being instantly displayed on screen.
    cbreak(); // Makes input available to terminal without use of ENTER
    
    keypad(stdscr, TRUE); // Enable input of arrow keys, F1,F2 etc
    
    // Initialize colors, if terminal does not support colors, exit.
    if(has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support colors, game ending...\n");
    }

    // Start NCurses coloring system.
    start_color();
    
    // Colors pairs, yellow text on black bg
    // Cyan on black bg
    // White on blue bg
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
}

void cleanup(void) {
    endwin();
}