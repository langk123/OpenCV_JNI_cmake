#include <jni.h>
#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>
#include <android/log.h>
#define  LOG_TAG    "JNI_PART"
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG, __VA_ARGS__)
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG, __VA_ARGS__)
#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG, __VA_ARGS__)
#define LOGF(...)  __android_log_print(ANDROID_LOG_FATAL,LOG_TAG, __VA_ARGS__)


using namespace cv;
using namespace std;
extern "C"{
JNIEXPORT void JNICALL
    Java_com_example_administrator_a20171023_MainActivity_nativeProcessFrame(JNIEnv*, jobject, jlong addrGray, jlong addrRgba)
    {
        Mat &mGr = *(Mat *) addrGray;
        Mat &mRgb = *(Mat *) addrRgba;
        vector<KeyPoint> v;

/*    LOGD("%d image size %d",mGr.rows,mGr.cols);
    resize(mGr,mGr,Size(mGr.cols*480/mGr.rows,480));
    LOGD("%d image new-size %d",mGr.rows,mGr.cols);*/

    Ptr<FeatureDetector> detector = FastFeatureDetector::create(50);
    detector->detect(mGr, v);
    for (unsigned int i = 0; i < v.size(); i++) {
        const KeyPoint &kp = v[i];
        circle(mRgb, Point(kp.pt.x, kp.pt.y), 10, Scalar(255, 255, 255, 255));
    }
    }

    JNIEXPORT jintArray JNICALL
    Java_com_example_administrator_a20171023_NDKloader_getGrayImage(
            JNIEnv *env,
            jclass type,
            jintArray pixels_,
            jint w, jint h) {
        jint *pixels = env->GetIntArrayElements(pixels_, NULL);
        // TODO
        if(pixels==NULL){
            return NULL;
        }
        cv::Mat imgData(h, w, CV_8UC4, pixels);
        uchar *ptr = imgData.ptr(0);
        for (int i = 0; i < w * h; i++) {
            int grayScale = (int) (ptr[4 * i + 2] * 0.299 + ptr[4 * i + 1] * 0.587
                                   + ptr[4 * i + 0] * 0.114);
            ptr[4 * i + 1] = (uchar) grayScale;
            ptr[4 * i + 2] = (uchar) grayScale;
            ptr[4 * i + 0] = (uchar) grayScale;
        }

        int size = w * h;
        jintArray result = env->NewIntArray(size);
        env->SetIntArrayRegion(result, 0, size, pixels);
        env->ReleaseIntArrayElements(pixels_, pixels, 0);
        return result;
    }


    JNIEXPORT jstring JNICALL
    Java_com_example_administrator_a20171023_MainActivity_stringFromJNI(
            JNIEnv *env,
            jobject /* this */) {
        std::string hello = "Hello from C++";
        return env->NewStringUTF(hello.c_str());
    }
}