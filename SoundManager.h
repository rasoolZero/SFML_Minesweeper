#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#include <SFML/Audio.hpp>
using namespace sf;
using namespace std;

class SoundManager
{
    public:
        enum Sounds{Explosion,Victory,FlagOn,FlagOff,Reveal,GameMusic,MenuMusic};
        SoundManager();
        void play(Sounds sound);
        void stop(Sounds sound);
        void stopAll();

    protected:

    private:
    vector<Sound> sounds;
    vector<SoundBuffer> buffers;
};

#endif // SOUNDMANAGER_H
