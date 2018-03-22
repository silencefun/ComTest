
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <jni.h>
#include <strings.h>


#include "android/log.h"
static const char *TAG = "serial_port";
#define LOGI(fmt, args...) __android_log_print(ANDROID_LOG_INFO,  TAG, fmt, ##args)
#define LOGD(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, TAG, fmt, ##args)
#define LOGE(fmt, args...) __android_log_print(ANDROID_LOG_ERROR, TAG, fmt, ##args)
int fd;
static speed_t getBaudrate(jint baudrate)
{
    switch(baudrate)
    {
        case 0:
            return B0;
        case 50:
            return B50;
        case 75:
            return B75;
        case 110:
            return B110;
        case 134:
            return B134;
        case 150:
            return B150;
        case 200:
            return B200;
        case 300:
            return B300;
        case 600:
            return B600;
        case 1200:
            return B1200;
        case 1800:
            return B1800;
        case 2400:
            return B2400;
        case 4800:
            return B4800;
        case 9600:
            return B9600;
        case 19200:
            return B19200;
        case 38400:
            return B38400;
        case 57600:
            return B57600;
        case 115200:
            return B115200;
        case 230400:
            return B230400;
        case 460800:
            return B460800;
        case 500000:
            return B500000;
        case 576000:
            return B576000;
        case 921600:
            return B921600;
        case 1000000:
            return B1000000;
        case 1152000:
            return B1152000;
        case 1500000:
            return B1500000;
        case 2000000:
            return B2000000;
        case 2500000:
            return B2500000;
        case 3000000:
            return B3000000;
        case 3500000:
            return B3500000;
        case 4000000:
            return B4000000;
        default:
            return -1;
    }
}

/**

* 设置串口数据，校验位,速率，停止位

* @param nBits 类型 int数据位 取值 位7或8

* @param nEvent 类型 char 校验类型 取值N ,E, O,,S

* @param mStop 类型 int 停止位 取值1 或者 2

*/

int set_opt(jint nBits, jchar nEvent, jint nStop)
{

    LOGE("set_opt:nBits=%d,nEvent=%c,nSpeed=%d,nStop=%d", nBits, nEvent, nStop);
    LOGE("set_opt:nStop=%d",  nStop);

    struct termios newtio;

    if(tcgetattr(fd, & newtio) != 0)
    {

        LOGE("setup serial failure");

        return -1;

    }

    bzero( & newtio, sizeof(newtio));

    //c_cflag标志可以定义CLOCAL和CREAD，这将确保该程序不被其他端口控制和信号干扰，同时串口驱动将读取进入的数据。CLOCAL和CREAD通常总是被是能的

    newtio.c_cflag |= CLOCAL | CREAD;


    switch(nBits) //设置数据位数
    {

        case 7:
            LOGE("设置数据位数==7");
            newtio.c_cflag &= ~CSIZE;

            newtio.c_cflag |= CS7;

            break;

        case 8:
            LOGE("设置数据位数==8");
            newtio.c_cflag &= ~CSIZE;

            newtio.c_cflag |= CS8;

            break;

        default:
            newtio.c_cflag &= ~CSIZE;

            newtio.c_cflag |= CS8;
            LOGE("设置数据位数==默认=8");
            break;

    }



    switch(nEvent) //设置校验位
    {
        case 'o':
        case 'O':

            newtio.c_cflag |= (PARODD | PARENB);
            newtio.c_iflag |= INPCK;
            LOGE("设置校验位O奇校验位");

            break;
        case 'e':
        case 'E':

            newtio.c_cflag |= PARENB;
            newtio.c_cflag &= ~PARODD;
            newtio.c_iflag |= INPCK;



            LOGE("设置校验位E偶校验位");

            break;

        case 'N':
        case 'n':
            newtio.c_cflag &= ~PARENB; //清除校验位


            LOGE("设置校验位N");
            break;


        default:
            newtio.c_cflag &= ~PARENB; //清除校验位
            LOGE("设置校验位默认N");
            break;

    }
    switch(nStop) //设置停止位
    {

        case 1:

            newtio.c_cflag &= ~CSTOPB;

            break;

        case 2:

            newtio.c_cflag |= CSTOPB;

            break;

        default:
            newtio.c_cflag &= ~CSTOPB;
            // LOGW("nStop:%d,invalid param", nStop);

            break;

    }

    newtio.c_cc[VTIME] = 0;//设置等待时间

    newtio.c_cc[VMIN] = 0;//设置最小接收字符

    tcflush(fd, TCIFLUSH);

    if(tcsetattr(fd, TCSANOW, & newtio) != 0)
    {

        LOGE("options set error");

        return -1;

    }


    LOGE("options set success");
    return 1;

}


/*
 * Class:     android_serialport_SerialPort
 * Method:    open
 * Signature: (Ljava/lang/String;II)Ljava/io/FileDescriptor;
 */
JNIEXPORT jobject JNICALL Java_com_silencefun_comtest_serialport_SerialPort_open
        (JNIEnv *env, jclass thiz, jstring path, jint baudrate,
         jint databits, jint stopbits, jchar parity)
{

    speed_t speed;
    jobject mFileDescriptor;

    /*波特率 */
    {
        speed = getBaudrate(baudrate);
        if (speed == -1)
        {
            /* TODO: throw an exception */
            LOGE("Invalid baudrate");
            return NULL;
        }
    }

    /* Opening device */
    {
        jint flags = 0;
        jboolean iscopy;
        const char *path_utf = (*env)->GetStringUTFChars(env, path, &iscopy);
        LOGD("Opening serial port %s with flags 0x%x", path_utf, O_RDWR | flags);
        fd = open(path_utf, O_RDWR | O_NONBLOCK);
        //fd=fd;
        LOGD("open() fd = %d", fd);
        (*env)->ReleaseStringUTFChars(env, path, path_utf);
        if (fd == -1)
        {
            /* Throw an exception */
            LOGE("Cannot open port");
            /* TODO: throw an exception */
            return NULL;
        }
    }

    /* Configure device */
    {
        struct termios cfg;
        LOGD("Configuring serial port");
        if (tcgetattr(fd, &cfg))
        {
            LOGE("tcgetattr() failed");
            close(fd);
            /* TODO: throw an exception */
            return NULL;
        }

        cfmakeraw(&cfg);
        //设置波特率
        cfsetispeed(&cfg, speed);
        cfsetospeed(&cfg, speed);

        if (tcsetattr(fd, TCSANOW, &cfg))
        {
            LOGE("tcsetattr() failed");
            close(fd);
            /* TODO: throw an exception */
            return NULL;
        }

        //配置校验位 停止位等等
        set_opt(databits, parity, stopbits);
    }

    /* Create a corresponding file descriptor */
    {
        jclass cFileDescriptor = (*env)->FindClass(env, "java/io/FileDescriptor");
        jmethodID iFileDescriptor = (*env)->GetMethodID(env, cFileDescriptor, "<init>", "()V");
        jfieldID descriptorID = (*env)->GetFieldID(env, cFileDescriptor, "descriptor", "I");
        mFileDescriptor = (*env)->NewObject(env, cFileDescriptor, iFileDescriptor);
        (*env)->SetIntField(env, mFileDescriptor, descriptorID, (jint)fd);
    }

    return mFileDescriptor;

}

/*
 * Class:     cedric_serial_SerialPort
 * Method:    close
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_silencefun_comtest_serialport_SerialPort_close
        (JNIEnv *env, jobject thiz)
{
    jclass SerialPortClass = (*env)->GetObjectClass(env, thiz);
    jclass FileDescriptorClass = (*env)->FindClass(env, "java/io/FileDescriptor");

    jfieldID mFdID = (*env)->GetFieldID(env, SerialPortClass, "mFd", "Ljava/io/FileDescriptor;");
    jfieldID descriptorID = (*env)->GetFieldID(env, FileDescriptorClass, "descriptor", "I");

    jobject mFd = (*env)->GetObjectField(env, thiz, mFdID);
    jint descriptor = (*env)->GetIntField(env, mFd, descriptorID);

    LOGD("close(fd = %d)", descriptor);
    close(descriptor);
}