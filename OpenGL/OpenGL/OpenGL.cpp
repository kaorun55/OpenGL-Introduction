// OpenGL.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

// ���̂�����̃y�[�W���Q�l�ɂ��Ă��܂�
// http://marina.sys.wakayama-u.ac.jp/~tokoi/oglarticles.html
// http://www.wakayama-u.ac.jp/~tokoi/opengl/libglut.html
// http://tkengo.github.io/blog/2014/12/20/opengl-es-2-2d-knowledge-0/

// GLUT,GLEW��NuGet�ɂăC���X�g�[�����Ă��܂�

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

    GLuint textureId1;
    GLuint textureId2;
    GLuint textureId3;
    GLuint textureId4;

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

        // GLEW �̏����� 
        GLenum err = glewInit();
        if ( err != GLEW_OK ) {
            throw std::runtime_error( std::string( "Error: " ) += std::string( (char*)glewGetErrorString( err ) ) );
        }
    }

    void initTexture()
    {
        auto loadTexture = []( const char* fileName, GLuint* textureId )
        {
            // �摜�f�[�^��ǂݍ���
            auto image = cv::imread( fileName );
            cv::cvtColor( image, image, CV_BGR2RGBA );

            // �e�N�X�`�����쐬����
            glGenTextures( 1, textureId );
            glBindTexture( GL_TEXTURE_2D, *textureId );

            glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, image.cols, image.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data );

            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
        };

        loadTexture( "texture1.png", &textureId1 );
        loadTexture( "texture2.jpg", &textureId2 );
        loadTexture( "texture3.jpg", &textureId3 );
        loadTexture( "texture4.jpg", &textureId4 );
    }

    static void displayHandler()
    {
        app->display();
    }

    void display()
    {
        glClear( GL_COLOR_BUFFER_BIT );
        glClearColor( 0.0, 0.0, 0.0, 1.0 );

        auto drawTexture = []( GLuint textureId,  const float* vertexes ) {
            glBindTexture( GL_TEXTURE_2D, textureId );

            // �e�N�X�`����L���ɂ���
            glEnable( GL_TEXTURE_2D );

            // �e�N�X�`����K�p�����l�p�`��`��
            glBegin( GL_QUADS );
            glTexCoord2d( 0.0, 1.0 ); glVertex3d( vertexes[0], vertexes[1], vertexes[2] );
            glTexCoord2d( 1.0, 1.0 ); glVertex3d( vertexes[3], vertexes[4], vertexes[5] );
            glTexCoord2d( 1.0, 0.0 ); glVertex3d( vertexes[6], vertexes[7], vertexes[8] );
            glTexCoord2d( 0.0, 0.0 ); glVertex3d( vertexes[9], vertexes[10], vertexes[11] );
            glEnd();

            glDisable( GL_TEXTURE_2D );
        };

        // �l�p������
        {
            float vertexes1[] = { 
                -1.0, 0.0, 0.0,
                 0.0, 0.0, 0.0,
                 0.0, 1.0, 0.0,
                -1.0, 1.0, 0.0 };
            drawTexture( textureId1, vertexes1 );

            float vertexes2[] = {
                0.0, 0.0, 0.0,
                1.0, 0.0, 0.0,
                1.0, 1.0, 0.0,
                0.0, 1.0, 0.0 };
            drawTexture( textureId2, vertexes2 );

            float vertexes3[] = {
                -1.0, -1.0, 0.0,
                0.0, -1.0, 0.0,
                0.0, 0.0, 0.0,
                -1.0, 0.0, 0.0 };
            drawTexture( textureId3, vertexes3 );

            float vertexes4[] = {
                0.0, -1.0, 0.0,
                1.0, -1.0, 0.0,
                1.0, 0.0, 0.0,
                0.0, 0.0, 0.0 };
            drawTexture( textureId4, vertexes4 );
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

