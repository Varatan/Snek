#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>

#define bufor_W 100
#define bufor_S 90
#define skala 9
#define disp_W skala*bufor_W
#define disp_S skala*bufor_S



int losuj_x() {
    return (((rand()%6) + 1)*15) -15;
}


int losuj_y() {
    return (((rand()%6)+1)*15) -15;
}

/*int losuj_x() {
    return (rand()%(bufor_S - 13));
}


int losuj_y() {
    return (rand() % (bufor_S - 15));
}*/


int main()
{
    srand(time(NULL)); // randomize seed
    al_init();
    al_install_keyboard();
    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    al_init_image_addon();
    al_init_font_addon();
    al_init_primitives_addon();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_DISPLAY* disp = al_create_display(disp_S, disp_W);
    ALLEGRO_BITMAP* bufor = al_create_bitmap(bufor_S, bufor_W);
    ALLEGRO_FONT* font = al_create_builtin_font();

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    ALLEGRO_BITMAP* dino_img = al_load_bitmap("SnekBody.png");
    ALLEGRO_BITMAP* head = al_load_bitmap("SnekHead.png");
    ALLEGRO_BITMAP* head1 = al_load_bitmap("SnekHead1.png");
    ALLEGRO_BITMAP* biwo_img = al_load_bitmap("NewBiwo.png");
    ALLEGRO_BITMAP* wyspa = al_load_bitmap("tlo.png");
    bool nowa_klatka = true, dzialaj = true;
    ALLEGRO_EVENT event;
    int sneksize = 15;
    int klatka = 0,dx=sneksize,dy=0,status=0,rum_x=0,rum_y=0,counter = 0,ruchstatus=1,genstatus=1,first=0,kierunek,updown;
    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));
    int woda = 0;

    struct snakeBody
    {
        int x;
        int y;
        int head;
    };

    struct snakeBody snakeMain[36];

    for(int i=0;i<=36;i++){
        snakeMain[i].x = -15;
        snakeMain[i].y = -15;
    }
    int snakeLen = 2;
    updown=0;
    snakeMain[0].x = 45;
    snakeMain[0].y = 45;
    snakeMain[0].head = 1;

    snakeMain[1].x = 30;
    snakeMain[1].y = 45;

    snakeMain[2].x = 15;
    snakeMain[2].y = 45;
    al_start_timer(timer);
    while (dzialaj)
    {
        al_wait_for_event(queue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_TIMER:
                if (status && key[ALLEGRO_KEY_ENTER]) {
                    for(int i=0;i<=36;i++){
                        snakeMain[i].x = -15;
                        snakeMain[i].y = -15;
                    }
                    snakeMain[0].x = 45;
                    snakeMain[0].y = 45;

                    snakeMain[1].x = 30;
                    snakeMain[1].y = 45;

                    snakeMain[2].x = 15;
                    snakeMain[2].y = 45;

                    snakeLen = 2;

                    dx = sneksize;dy = 0;
                    status = 0; woda = 0;
                    counter = 0;
                    key[ALLEGRO_KEY_ENTER] = 0;
                }
                if (!status && key[ALLEGRO_KEY_RIGHT] && dx!=-sneksize && ruchstatus==1){
                    dx=sneksize;
                    dy=0;
                    ruchstatus = 0;
                    kierunek = 0;
                    updown=0;
                }
                if (!status && key[ALLEGRO_KEY_LEFT] && dx!=sneksize && ruchstatus==1){
                    dx=-sneksize;
                    dy=0;
                    ruchstatus = 0;
                    kierunek = ALLEGRO_FLIP_HORIZONTAL;
                    updown=0;
                }
                if (!status && key[ALLEGRO_KEY_UP] && dy !=sneksize && ruchstatus==1){
                    dy=-sneksize;
                    dx=0;
                    ruchstatus = 0;
                    updown=1;
                    kierunek=0;
                }
                if (!status && key[ALLEGRO_KEY_DOWN] && dy!= -sneksize && ruchstatus==1){
                    dy=sneksize;
                    dx=0;
                    ruchstatus = 0;
                    updown=1;
                    kierunek = ALLEGRO_FLIP_VERTICAL;
                }

                if (!status && klatka % 20 == 0) {
                    if (snakeMain[0].x + dx < 0) status = 1;//dx = 1; lewo
                    if (snakeMain[0].x + dx > bufor_S -15) status = 1;// dx = -1; prawo
                    if (snakeMain[0].y + dy < 0) status = 1;// dy = 1; gora
                    if (snakeMain[0].y + dy > bufor_W -25) status = 1;// dy = -1; dol
                    for(int i = 1;i<snakeLen;i++){
                        if(snakeMain[0].x == snakeMain[i].x && snakeMain[0].y == snakeMain[i].y){
                            status = 1;
                        }
                    }
                    if(status!=1){
                        for(int x=snakeLen; x>=0; x--){
                            snakeMain[x+1]=snakeMain[x];
                        }
                        snakeMain[0] = snakeMain[1];
                        snakeMain[snakeLen+1].x = 0;
                        snakeMain[snakeLen+1].y = 0;
                        snakeMain[0].x += dx;
                        snakeMain[0].y += dy;
                        //printf("x: %d ",snakeMain[0].x);
                        //printf("y: %d\n",snakeMain[0].y);
                        ruchstatus = 1;
                    }
                }
                if (!rum_x && !rum_y) {
                    rum_x = losuj_x();
                    if(rum_x == 0) rum_x = 1;
                    rum_y = losuj_y();
                    if(rum_y == 0) rum_y = 1;
                    //printf("X:%d Y:%d\n",rum_x,rum_y);
                    genstatus = 1;
                    while(genstatus){
                        for(int i = 0;i<=snakeLen;i++){
                            //printf("for\n");
                            printf("X:%d Y:%d\n",rum_x,rum_y);
                            printf("SnekX:%d SnekY:%d\n",snakeMain[i].x,snakeMain[i].y);
                            if(abs(rum_x - snakeMain[i].x) < 2 && abs(rum_y - snakeMain[i].y) < 2){
                                printf("petla\n");
                                rum_x = losuj_x();
                                if(rum_x == 0) rum_x = 1;
                                rum_y = losuj_y();
                                if(rum_y == 0) rum_y = 1;
                                i = 0;
                            }
                            if(i==snakeLen){
                                if(abs(rum_x - snakeMain[i].x) >1 || abs(rum_y - snakeMain[i].y) > 1){
                                    genstatus =0;
                                    printf("jest git\n");
                                }
                            }
                        }
                    }
                    if(first){
                        snakeLen++;
                        snakeMain[snakeLen].x = snakeMain[snakeLen-1].x;
                        snakeMain[snakeLen].y = snakeMain[snakeLen-1].y;
                    }
                    first = 1;
                }
                if ((abs(snakeMain[0].x - rum_x) + abs(rum_y - snakeMain[0].y)) < 14)
                {
                    rum_x = rum_y = 0;
                    counter++;
                }
                if (key[ALLEGRO_KEY_ESCAPE ]) dzialaj = false;
                nowa_klatka = true;
                klatka+=1; // predkosc animacji
                if (klatka > 240) klatka = 1;
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                key[event.keyboard.keycode] = 1;
                break;
            case ALLEGRO_EVENT_KEY_UP:
                key[event.keyboard.keycode] = 0;
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE :
                dzialaj = false;
        }
        if (nowa_klatka && al_is_event_queue_empty(queue))
        {
            al_set_target_bitmap(bufor);
            //-----------------
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_bitmap(wyspa, 0, 0, 0);
            al_draw_textf(font, al_map_rgb(255, 255, 255), 1, 92, 0, "Score:%d", counter);
            int k;//int kk = 4;
            if (status == 1) {
                woda++;
            }
            //else k = (klatka / 30) % 3;
            //int strona = (dx > 0 ? 0 : ALLEGRO_FLIP_HORIZONTAL);
            if (rum_x && rum_y) {
                al_draw_filled_ellipse(rum_x+6, rum_y+15, 10, 4, al_map_rgba(0, 0, 0, 64));
                al_draw_bitmap(biwo_img, rum_x, rum_y, 0);
            }
            if (woda < 60 ) {
                for(int i=0;i<=snakeLen;i++){
                    if(i==0){
                        if(updown==0){
                            al_draw_bitmap(head, snakeMain[i].x, snakeMain[i].y, kierunek);
                        }else{
                            al_draw_bitmap(head1, snakeMain[i].x, snakeMain[i].y, kierunek);
                        }

                    }else{
                        al_draw_bitmap(dino_img, snakeMain[i].x, snakeMain[i].y, kierunek);
                    }

                }
            }
            else {
                key[ALLEGRO_KEY_ENTER] = 1;
            }
            al_set_target_backbuffer(disp);
            al_draw_scaled_bitmap(bufor,0,0,bufor_S, bufor_W, 0,0,disp_S,disp_W,0);
            al_flip_display();
            nowa_klatka = false;
        }
    }
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    return 0;
}