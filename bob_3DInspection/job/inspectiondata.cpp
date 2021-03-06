#include "inspectiondata.hpp"

using namespace std;
using namespace Job;
using namespace SSDK;

InspectionData::InspectionData()
{
    this->m_version = "";
    this->m_lastEditingTime = "";
}

InspectionData::~InspectionData()
{

}

void InspectionData::writeInspectionDataToXml(QString path)
{
    try
    {
        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        //step1
        //定义一个QDomDocument xml文档类的对象
        //在该文档下生成一个jobInfo节点,将版本号,上次编辑时间写入在该节点下
        QDomDocument inspectionData;
        //在文档中增加一个jobInfo元素
        QDomElement jobInfo = inspectionData.createElement("Job");

        //设置jobInfo元素的属性(版本号,上次编辑时间)
        jobInfo.setAttribute("版本号",
                             QString::fromStdString(this->version()));
        jobInfo.setAttribute("上次编辑时间",
                             QString::fromStdString(this->lastEditingTime()));
        //将jobInfo元素的属性添加到 inspectionData 对象中
        inspectionData.appendChild(jobInfo);
        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        //step2
        //将board信息写入到inspectionData文档中的jobInfo节点下
        this->pBoard()->writeBoardDataToXml(inspectionData,jobInfo);
        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        //step3
        //设置文件路径,并将inspectionData中的数据写入到该路径下的xml文件中
        QFile file(path);
        //判断文件是否被打开,文档为只写模式,文档格式是文本格式
        if (!file.open(QFile::WriteOnly | QFile::Text))
        {
            THROW_EXCEPTION("打开文件失败!!");
        }
        //定义文本输出流
        QTextStream out(&file);
        //保存文本文档,输出内容空4格
        inspectionData.save(out,4);
        //关闭文件
        file.close();
        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    }
    catch(const exception &ex)
    {
        THROW_EXCEPTION(ex.what());
    }
}
