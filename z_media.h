#ifndef Z_MEDIA_H_INCLUDED
#define Z_MEDIA_H_INCLUDED

//THIS FILE IS JUST TO MAKE LINKING EASIER TO MANAGE
//

//Maths
//
#include "z_maths/z_math.h"

//Window
#include "z_media/window.h"

//Visual media
#include "z_media/images.h"
#include "z_media/shape.h"
#include "z_media/text.h"

//BUNDLING EVENT STUFF
//
struct button_bundle{
public:
    int search_rectangle(SDL_Rect obs_rect){
        //
        //NOTE: THIS IS ALL ASSUMING THE BUTTONS ARE SORTED LEAST TO GREATEST FROM X TO Y TO W THEN H
        //
        int i,j,k,n;
        i = 0;
        j = int(rectangles.size()-1);

        int l[j];

        //CHECKING X COORDS FIRST
        //
        for (n = 0; n < j; n++)
            l[n] = rectangles.at(n).x;

        if ((i = lin_search_num(l,0,j,obs_rect.x)) > -1){
            //DONT HAVE TO GO THROUGH THE REST OF THE LIST
            //
            k = i;
            //CHECKING Y COORDS
            //
            for (n = k; n < j; n++)
                l[n] = rectangles.at(n).y;

            if ((i = lin_search_num(l,k,j,obs_rect.y)) > -1){
                k = i;

                for (n = k; n < j; n++)
                    l[n] = rectangles.at(n).w;

                if ((i = lin_search_num(l,k,j,obs_rect.w)) > -1){
                    k = i;

                    for (n = k; n < j; n++)
                        l[n] = rectangles.at(n).w;

                    return lin_search_num(l,k,j,obs_rect.h);
                } else
                    return i;
            } else
                return i;
        } else
            return i;
    };

    void move_rectangles(int x_move = 0, int y_move = 0){

        for (int i = 0; i < int(rectangles.size()); i++){
            rectangles[i].x = rectangles[i].x + x_move;
            rectangles[i].y = rectangles[i].y + y_move;
        }
    }

    button m_button;
    std::vector<SDL_Rect> rectangles;
};

//BUNDLING VISUALS (FOR REPEATED RENDERING)
//
struct image_bundle{
public:
    void render_bundle(int x_pos = 0, int y_pos = 0, int x_size = 1, int y_size = 1){
        int i, j = int(points.size()), render_x, render_y;

        if (m_image.get_active())
            for (i = 0; i < j; i++){
                render_x = points[i].get_x()-x_pos;
                render_y = points[i].get_y()-y_pos;

                //CHECKING IF RENDERING SPOT IS WITHIN BOUNDS
                //
                if (render_x+m_image.get_x_clip() > 0 && render_x < x_size && render_y+m_image.get_y_clip() > 0 && render_y < y_size)
                    m_image.render(render_x,render_y);
            }
    };

    int search_point(point given_point){
        for (int i = 0; i < int(points.size()); i++)
            if (given_point.get_x() == points[i].get_x() && given_point.get_y() == points[i].get_y())
                return i;

        return -1;
    };

    image m_image;
    std::vector<point> points;
};

struct text_bundle{
public:
    void render_bundle(int x_pos = 0, int y_pos = 0, int x_size = 1, int y_size = 1){
        int i, j = int(points.size()), render_x, render_y;

        if (m_text.get_active())
            for (i = 0; i < j; i++){
                render_x = points[i].get_x()-x_pos;
                render_y = points[i].get_y()-y_pos;

                if (render_x+m_text.get_x_size() > 0 && render_x < x_size && render_y+m_text.get_y_size() > 0 && render_y < y_size)
                    m_text.render(render_x,render_y);
            }
    };

    int search_point(point given_point){
        for (int i = 0; i < int(points.size()); i++)
            if (given_point.get_x() == points[i].get_x() && given_point.get_y() == points[i].get_y())
                return i;

        return -1;
    };

    text m_text;
    std::vector<point> points;
};

struct shape_bundle{
public:
    void render_bundle(int x_pos = 0, int y_pos = 0, int x_size = 1, int y_size = 1){
        int i, j = int(points.size()),render_x, render_y;

        if (m_shape.get_active())
            for (i = 0; i < j; i++){
                render_x = points[i].get_x()-x_pos;
                render_y = points[i].get_y()-y_pos;

                if (render_x+m_shape.get_x_size() > 0 && render_x < x_size && render_y+m_shape.get_y_size() > 0 && render_y < y_size)
                    m_shape.render(render_x,render_y);
            }
    };

    int search_point(point given_point){
        for (int i = 0; i < int(points.size()); i++)
            if (given_point.get_x() == points[i].get_x() && given_point.get_y() == points[i].get_y())
                return i;

        return -1;
    };

    shape m_shape;
    std::vector<point> points;
};

//Audio media
#include "z_media/sound.h"

#endif // Z_MEDIA_H_INCLUDED
