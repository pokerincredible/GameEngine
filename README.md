# GameEngine
Follow ThinMatrix‘s LearnOpenGL



### bug

1. 将 openmesh 相关的 lib 和 dll 加入到项目中后目前只能在 release 模式下运行成功，安装后的 OpenMesh 不存在这个问题，也不区分 Debug 和 Release 版的文件
2. 删除了 OpenMesh 的引用，导出模型不知道如何导出 texcoord，api 太难用