#include <iostream>
// #include "demuxer/demuxer.h"
#include <string>
#include <dirent.h>
#include <cstring>
#include "audio-censor-service/audio-censor.h"
using namespace std;



int main()
{
    char *video_path = "/home/diaoaijie/workspace/video-censor-service2/SampleVideo_1280x720_5mb.mp4";
    char *outaudio_path = "outaudio.aac";
    char *outvideo_path = "outvideo.h264";
    char out_audio_cmd[256];
    char out_video_cmd[256];
    sprintf(out_audio_cmd,"ffmpeg -i %s -vn -c:a copy %s",video_path,outaudio_path);
    // sprintf(out_video_cmd,"ffmpeg -i %s -vn -c:a copy %s",video_path,outvideo_path);
    system(out_audio_cmd);
    // system(out_video_cmd);
    cout<<"音视频分离完毕"<<endl;
    char *wav_audio_path = "output.wav";
    char do_audio_cmd[256] ;
    sprintf(do_audio_cmd,"ffmpeg -i %s -acodec pcm_s16le -ar 16000 -ac 1 %s",outaudio_path,wav_audio_path);
    system(do_audio_cmd);
    string audioresult;
    doCensor(wav_audio_path,audioresult);

    char *image_dir = "../../../images";
    char do_video_cmd[256];
    sprintf(do_video_cmd,"ffmpeg -i %s -vf fps=1 ../../../%s/out%%d.jpg",video_path,image_dir);
    system(do_video_cmd);
    cout<<"抽帧ending "<<do_video_cmd<<endl;
    DIR *dir = opendir(image_dir);
    cout<<"image_dir"<<image_dir<<endl;
    if (dir == nullptr) {
        std::cerr << "Could not open directory." << std::endl;
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != nullptr) {
        // 过滤掉 "." 和 ".." 目录
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            char image_path[256];
            sprintf(image_path,"%s/%s",image_dir,entry->d_name);
            cout<<image_path<<endl;
            char cmd[256];
            sprintf(cmd,"../../../image-service2/test %s",image_path);
            system(cmd);
        }
    }
    closedir(dir);
    return 0;
}