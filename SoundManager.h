#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#include <SFML/Audio.hpp>
using namespace sf;
using namespace std;

class SoundManager
{
    public:
        SoundManager();

    protected:

    private:
    vector<Sound> sounds;
    vector<SoundBuffer> buffers;
};

#endif // SOUNDMANAGER_H
