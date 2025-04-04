Asset 模块负责资源的导入, 导出, 管理
其核心类为: AssetManager 负责整体接口的封装。
AssetManager{

Import * importor;
Export * exportor;

};

因为这里3D资产的导入是通过第三方库来完成的, 所以 Import 和 Export 提供的是一个接口声明。
即便是更换第三方库, 也应该实现接口的功能。

Import 将第三方库解析出的格式存放一个公共缓冲区的类 AssetBuffer 中, Export 负责读取 AssetBuffer 中的数据。

Import -> Asset -> Export
