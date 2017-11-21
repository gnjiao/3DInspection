#include "capturesetting.hpp"

using namespace std;
using namespace App;


void CaptureSetting::readCaptureSetting(const QString &path)
{
    try
    {
        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        //step1
        //如果文件不存在,则直接抛出异常信息
        if(!QFile::exists(path))
        {
            THROW_EXCEPTION("读取CapturSetting文件失败!");
        }

        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        //step2
        //如果文件存在,则读取文件中相对应的数据
        else
        {
            //将类QSettings实例化一个对象
            //path:存放文件的路径
            //QSettings::IniFormat: 为存放文件的格式
            QSettings configFile(path,QSettings::IniFormat);

            //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            //step2.1
            //读取文件Image/Width数据,并判断是否与系统默认值匹配,如果不匹配,则抛出异常
            int width = configFile.value("Image/Width").toInt();

            if(width != CaptureSetting::imgWidth)
            {
                THROW_EXCEPTION("读取文件数据Image/Width失败!");
            }
            //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

            //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            //step2.2
            //读取文件Image/Height数据,并判断是否与系统默认值匹配,如果不匹配,则抛出异常
            int height = configFile.value("Image/Height").toInt();

            if(height !=  CaptureSetting::imgHeight)
            {
                THROW_EXCEPTION("读取文件数据Image/Height失败!");
            }
            //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

            //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            //step2.3
            //读取文件Image/ImgBit数据,并判断是否与系统默认值匹配,如果不匹配,则抛出异常
            int imgBit = configFile.value("Image/ImgBit").toInt();

            if(imgBit !=  CaptureSetting::imgBitArr[0] &&
               imgBit !=  CaptureSetting::imgBitArr[1])
            {
                THROW_EXCEPTION("读取文件数据Image/ImgBit失败!");
            }
            //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        }
        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    }
    catch (const exception &ex)
    {
        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        //捕获异常,并在终端显示
        cout<<ex.what()<<endl;
        cout<<"检测功能不能用,请重新标定!"<<endl;
        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    }
}

void CaptureSetting::writeCaptureSetting(const QString &path)
{
    //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //将类QSettings实例化一个对象
    //path:存放文件的路径
    //QSettings::IniFormat: 为存放文件的格式
    QSettings configFile(path,QSettings::IniFormat);

    //将Image/Width的数据写为系统默认值,默认为"4096"
    configFile.setValue("Image/Width",CaptureSetting::imgWidth);
    //将Image/Height的数据写为系统默认值,默认为"3072"
    configFile.setValue("Image/Height",CaptureSetting::imgHeight);
    //将Image/Height的数据写为系统默认值,默认为"8"
    configFile.setValue("Image/ImgBit",CaptureSetting::imgBitArr[0]);

    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
}
