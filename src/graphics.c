// graphics.c
#include "graphics.h"

// The actual thousands of lines of ASCII go here.
// 'const' ensures it stays safely in Flash memory.
const char *ui_line = "+==============================================================================+";
const char *ui_info = "|    Success rate: XXX%    |    Location: XXXXXXXXXXX    |     Time: XX:XX     |";

const char *boss_frame_2[] = {
    "  *+++*+***+****+***+******+*+********++*++*+**+*+#**#+#+",
    "  +#++##++*#*+++#+*++*+*+++++++++*+#++**+*+*+#+#**+++++*+",
    // ... 20 more lines ...
};