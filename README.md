 组件化架构的目标是告别结构臃肿，让各个业务变得相对独立，业务组件在组件模式下可以独立开发，而在集成模式下又可以变为组件包集成到相关壳工程中，组成一 个完整功能的应用程序； 从组件化工程模型中可以看到，业务组件之间是独立的，没有关联的，这些业务组件在集成模式下是一个个Class，不依赖工程文件，组成一个具有完整独立业务功能的应用， 但是在组件开发模式下，业务组件又变成了一个个应用程序，它们可以独立开发和调试， 由于在组件开发模式下，业务组件们的代码量相比于完整的项目差了很远，因此在运行时可 以显著减少编译时间。
 
 组件化开发优势
 
 1、加快业务迭代速度，模块独立，相互依赖比较少
 2、公用模块稳定，可以提供各个业务线独立使用。
 3、迭代频繁，互不干涉。
 3、业务配置灵活，可以随时上线下线
 4、编译速度快。
 5、颗粒化控制更加精确。
 6、配置更加灵活，独立组件修改可以独立上线。
 
 代码说明
 
 ComponentCore 文件夹下主要是内核程序，主要进行YML解析，字符串处理，通用数据类型，以及动态加载等c++代码
 
 ComponentDev 文件夹主要是主应用程序，主要处理动态库的加载，以及config文件
 
 TestDll 测试文件夹
 
 ComDllTest 测试文件夹
