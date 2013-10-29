/* Standard libraries */
#include <fstream>
#include <string>

/* SDL */
#include <SDL2/SDL.h>

/* Local headers */
#include "utils.h"


/* quit_all()
 * Performs deinitialisation shit required before an exit
 */
void quit_all()
{
    SDL_Quit();
}


/* read_file_contents(const char *filename)
 * Takes filename and returns
 * a string of file's entire contents.
 */
std::string read_file_contents(const char *filename)
{
    std::string str;
    std::ifstream file(filename, std::ios::in | std::ios::binary);

    if (!file) {
        str.clear();
        return str;
    }

    file.seekg(0, std::ios::end);
    str.resize(file.tellg());

    file.seekg(0, std::ios::beg);
    file.read(&str[0], str.size());

    return str;
}
