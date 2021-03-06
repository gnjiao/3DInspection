#include "appsetting.hpp"

using namespace App;
using namespace std;


AppSetting::AppSetting()
{
    //初始化成员变量
    this->m_companyName = "";
}

AppSetting::~AppSetting()
{

}

void AppSetting::readAppSetting(const QString &path)
{
    try
    {
        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        //step1
        //判断配置文件在目录中是否存在
        //将数据写入至配置文件中
        if(!QFile::exists(path))
        {
            writeAppSetting(path);
        }
        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        //step2
        //如果配置文件存在,则读取文件中相应的数据并判断数据是否符合要求
        //如果数据不符合要求,则将该字段数据写为默认值
        else
        {
            //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            //step2.1
            //读取文件Theme内容,并判断是否在枚举中,如果不在则写入默认值
            QSettings configFile(path,QSettings::IniFormat);

            QString theme = configFile.value("Theme").toString();

            //判断当前主题是否在枚举中,如果不在,则写入默认值
            if( theme.toUpper().toStdString() == VAR_TO_STR(THEME::BLACK) )
            {
                this->m_theme = THEME::BLACK;
            }
            else if (theme.toUpper().toStdString() != VAR_TO_STR(THEME::WHITE))
            {
                this->m_theme = THEME::WHITE;
            }
            else
            {
                configFile.setValue("Theme","Black");
                this->m_theme = THEME::BLACK;
            }
            //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

            //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            //step2.2
            //读取文件Lang内容,并判断是否在枚举中,如果不在则写入默认值
            QString lang = configFile.value("Lang").toString();

            if(lang.toUpper().toStdString() == VAR_TO_STR(LANG::CN))
            {
                this->m_lang = LANG::CN;
            }
            else if ( lang.toUpper().toStdString() == VAR_TO_STR(LANG::EN) )
            {
                this->m_lang = LANG::EN;
            }
            else
            {
                configFile.setValue("Lang","CN");
            }
            //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

            //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            //step2.3
            //读取文件LaneMode内容,并判断是否在枚举中,如果不在则写入默认值

            QString laneMode = configFile.value("LaneMode").toString();

            if(laneMode.toUpper().toStdString() == VAR_TO_STR(LANEMODE::SIMULATOR))
            {
                this->m_laneMode = LANEMODE::SIMULATOR;
            }
            else if (laneMode.toUpper().toStdString() == VAR_TO_STR(LANEMODE::SINGLE_LANE))
            {
                this->m_laneMode = LANEMODE::SINGLE_LANE;
            }
            else if(laneMode.toUpper().toStdString() == VAR_TO_STR(LANEMODE::DUAN_LANE))
            {
                this->m_laneMode = LANEMODE::DUAN_LANE;
            }
            else
            {
                configFile.setValue("LaneMode","Single_Lane");
                this->m_laneMode = LANEMODE::SINGLE_LANE;
            }
            //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

            //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            //step2.4
            //读取文件MachineType内容,并判断是否在枚举中,如果不在则写入默认值
            QString machineType = configFile.value("MachineType").toString();

            if( machineType.toUpper().toStdString() == VAR_TO_STR(MACHINETYPE::AOI))
            {
                this->m_machineType = MACHINETYPE::AOI;
            }
            else if (machineType.toUpper().toStdString() == VAR_TO_STR(MACHINETYPE::SPI))
            {
                this->m_machineType = MACHINETYPE::SPI;
            }
            else
            {
                configFile.setValue("MachineType","AOI");
                this->m_machineType = MACHINETYPE::AOI;
            }
            //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

            //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            //step2.5
            //读取文件CompanyName内容,并判断是否在枚举中,如果不在则写入默认值
            this->m_companyName = configFile.value("Company").toString().toStdString();
            //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        }
        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    }
    //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //如果捕获异常,则输出异常信息
    catch(const exception &ex)
    {
        THROW_EXCEPTION(ex.what());
    }
    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
}

void AppSetting::writeAppSetting(const QString &path)
{
    //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //将类QSettings实例化一个对象
    //path:存放文件的路径
    //QSettings::IniFormat: 为存放文件的格式
    QSettings configFile(path,QSettings::IniFormat);

    //将配置文件的"Theme","CompanyName","MachineType","LaneMode","Lang"写入默认值
    configFile.setValue("Theme","Black");
    configFile.setValue("MachineType","AOI");
    configFile.setValue("LaneMode","Single_Lane");
    configFile.setValue("Lang","CN");
    configFile.setValue("Company","Scijet");
    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
}
