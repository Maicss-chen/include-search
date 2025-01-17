#include <iostream>
#include <PackageKit.h>

int main() {

    PackageKit::PackageKit p;

    //设置进度更新时的回调函数
    p.setProgressCallback([](int progress,PackageKit::TaskType type){
        std::string str;
        if(type == PackageKit::TASK_FIND_PACKAGE)
            str = "查找进度：";
        else if(type == PackageKit::TASK_INSTALL_PACKAGE)
            str = "安装进度：";
        else if(type == PackageKit::TASK_REMOVE_PACKAGE)
            str = "卸载进度：";
        std::cout<<"\r"<<str<<progress<<"%"<< std::flush; //flush作用是及时输出（清楚缓冲区）
    });

    //生成一个要查找包的包名列表
    std::vector<std::string> values;
    values.emplace_back("zsh");

    //获取查找结果
    std::cout<<"正在搜索...\n";
    auto pkg_list = p.find_packages_based_on_names_sync(values);

    //筛选
    std::vector<PackageKit::PkPackage> install_list;
    for(auto pkg : pkg_list){
        //将架构为x86_64的未安装的软件包加入安装列表
//        if(strcmp(pkg.get_package_arch(),"x86_64") == 0 && pkg.is_installed()){
            install_list.emplace_back(pkg);
//        }
    }

    //根据筛选结果提示和安装
    if(install_list.empty()){
        std::cout<<"\n您没有任何需要安装的软件包。\n";
    } else{
        std::cout<<"\n将安装以下软件包：\n";
        for(auto pkg : install_list){
            std::cout<<pkg.get_package_id()<<std::endl;
        }
        std::cout<<"开始安装...\n";
        //安装所有软件包
//        p.install_packages(install_list);
//        p.remove_packages(install_list);
        std::cout<<"\n安装完成"<<std::endl;
    }
    return 0;
}
