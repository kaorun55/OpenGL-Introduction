// OpenGL.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

// このあたりのページを参考にしています
// http://marina.sys.wakayama-u.ac.jp/~tokoi/oglarticles.html
// http://www.wakayama-u.ac.jp/~tokoi/opengl/libglut.html
// http://tkengo.github.io/blog/2014/12/20/opengl-es-2-2d-knowledge-0/

// GLUT,GLEWはNuGetにてインストールしています

#include "stdafx.h"

#include <iostream>

#include <GL\glew.h>
#include <GL\glut.h>

#include <opencv2\opencv.hpp>

class App
{
    static App* app;

    static const int width = 640;
    static const int height = 480;

    GLuint textureId;

public:
    App()
    {
        app = this;
    }

    void init( int argc, char* argv[] )
    {
        initOpenGL( argc, argv );
        initTexture();
    }

    void run()
    {
        glutMainLoop();
    }

private:

    void initOpenGL( int argc, char* argv[] )
    {
        glutInit( &argc, argv );
        glutInitDisplayMode( GLUT_RGB );
        glutInitWindowSize( width, height );
        glutCreateWindow( "OpenGL" );

        glutIdleFunc( displayHandler );
        glutDisplayFunc( displayHandler );
        //glutKeyboardFunc( keyboard );

        // GLEW の初期化 
        GLenum err = glewInit();
        if ( err != GLEW_OK ) {
            throw std::runtime_error( std::string( "Error: " ) += std::string( (char*)glewGetErrorString( err ) ) );
        }
    }

    void initTexture()
    {
        // 画像データを読み込む
        auto image = cv::imread("texture1.png");
        cv::cvtColor( image, image, CV_BGR2RGBA );

        // テクスチャを作成する
        glGenTextures( 1, &textureId );
        glBindTexture( GL_TEXTURE_2D, textureId );

        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, image.cols, image.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data );

        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    }

    static void displayHandler()
    {
        app->display();
    }

    void display()
    {
        glClear( GL_COLOR_BUFFER_BIT );
        glClearColor( 0.0, 0.0, 0.0, 1.0 );

        // 四角を書く
        {
            // テクスチャを有効にする
            glEnable( GL_TEXTURE_2D );

            // テクスチャを適用した四角形を描く
            glBegin( GL_QUADS );
            glTexCoord2d( 0.0, 1.0 ); glVertex3d( -1.0, -1.0, 0.0 );
            glTexCoord2d( 1.0, 1.0 ); glVertex3d( 1.0, -1.0, 0.0 );
            glTexCoord2d( 1.0, 0.0 ); glVertex3d( 1.0, 1.0, 0.0 );
            glTexCoord2d( 0.0, 0.0 ); glVertex3d( -1.0, 1.0, 0.0 );
            glEnd();

            glDisable( GL_TEXTURE_2D );
        }

        glFlush();
    }
};

/*static*/ App* App::app;


int main( int argc, char* argv[] )
{
    try
    {
        App app;
        app.init( argc, argv );
        app.run();
    }
    catch ( const std::exception& ex )
    {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}

