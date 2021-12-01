# Lua package loading

1. 生成chunk push到栈顶
2. 创建table，设置给_G表 _G["pkg"] = {}
3. 给这个table设置元表，元表继承_G表的访问域(__index)
4. 设置upvalue
5. 执行code chunk