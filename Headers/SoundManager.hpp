#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

class SoundManager
{
private:
    ALLEGRO_SAMPLE * fall;
    ALLEGRO_SAMPLE_ID * idFall;
    ALLEGRO_SAMPLE * die;
    ALLEGRO_SAMPLE * win;
    ALLEGRO_SAMPLE * menu;
    ALLEGRO_SAMPLE * coin;
    ALLEGRO_SAMPLE * background;
    ALLEGRO_SAMPLE * dig;
    ALLEGRO_SAMPLE * clickMenu;
    bool isPlaying;
    
public:
    SoundManager();
    ~SoundManager();
    void playFall();
    void playDie();
    void playWin();
    void playMenu();
    void playCoin();
    void playBackground();
    void playDig();
    void playClick();
    void stopFall();
    void stopDie();
    void stopWin();
    void stopMenu();
    void stopCoin();
    void stopBackground();
    void stopDig();
    void stopClick();
};