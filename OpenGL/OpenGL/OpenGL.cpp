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

class App
{
    static App* app;

    static const int width = 640;
    static const int height = 480;

public:
    App()
    {
        app = this;
    }

    void init( int argc, char* argv[] )
    {
        glutInit( &argc, argv );
        glutInitDisplayMode( GLUT_RGB );
        glutInitWindowSize( width, height );
        glutCreateWindow( "OPenGL" );

        glutIdleFunc( displayHandler );
        glutDisplayFunc( displayHandler );
        //glutKeyboardFunc( keyboard );

        // GLEW の初期化 
        GLenum err = glewInit();
        if ( err != GLEW_OK ) {
            fprintf( stdout, "Error: %s\n", glewGetErrorString( err ) );
            throw std::runtime_error( std::string( "Error: " ) += std::string( (char*)glewGetErrorString( err ) ) );
        }
    }

    void run()
    {
        glutMainLoop();
    }

private:

    static void displayHandler()
    {
        app->display();
    }

    void display()
    {
        glClear( GL_COLOR_BUFFER_BIT );
        glClearColor( 0.0, 0.0, 0.0, 1.0 );

        // 四角を書く
        glBegin( GL_QUADS );
        glColor3f( 1.0, 0.0, 0.0 ); glVertex3d( -0.5, -0.5, 0.0 );
        glColor3f( 1.0, 1.0, 0.0 ); glVertex3d( 0.5, -0.5, 0.0 );
        glColor3f( 1.0, 1.0, 1.0 ); glVertex3d( 0.5, 0.5, 0.0 );
        glColor3f( 1.0, 0.0, 1.0 ); glVertex3d( -0.5, 0.5, 0.0 );
        glEnd();

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

