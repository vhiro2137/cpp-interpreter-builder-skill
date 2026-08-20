# C++ 解释器构建 Skill

[English](README.md) | 简体中文

这是一个用于设计、实现、扩展和调试现代 C++17/20 解释器的 Codex Skill。它将《Crafting Interpreters》中的工程方法转化为按依赖顺序推进、由测试驱动的 C++ 工作流，同时覆盖 Tree-walk Interpreter 和字节码虚拟机两条路线。

## 安装

将本仓库复制到 Codex 的个人 Skill 目录：

```powershell
Copy-Item -Recurse cpp-interpreter-builder-skill "$env:USERPROFILE\.codex\skills\cpp-interpreter-builder"
```

目标文件夹名称应与 Skill 名称一致，即 `cpp-interpreter-builder`。

也可以让 Codex 使用内置的 `skill-installer` 从 GitHub 安装：

```text
$skill-installer 从 GitHub 仓库 vhiro2137/cpp-interpreter-builder-skill 安装 Skill。
```

## 使用

在新的 Codex 任务中显式调用：

```text
$cpp-interpreter-builder 检查这个 C++ 解释器，并实现下一个可验证阶段。
```

当任务涉及 C++ 扫描器、解析器、AST、Resolver、闭包、Tree-walk Interpreter、字节码编译器、虚拟机或相关故障排查时，Codex 也可以自动选择该 Skill。

## 内容

- `SKILL.md`：触发条件、参考资料路由和实施工作流。
- `references/`：按当前开发阶段按需加载的工程指导。
- `assets/project-template/`：可编译的 C++20/CMake 起始模板。
- `scripts/`：安全的项目脚手架和 AST 生成辅助脚本。

## 工作方式

Skill 会先检查现有项目、构建系统、测试和语言规范，然后识别当前处于扫描、解析、语义解析、Tree-walk 求值、字节码编译或 VM 执行的哪个阶段。它会选择一个最小可验证的纵向切片，完成实现、构建、测试和运行验证，而不是要求一次完成整门语言。

在参考或复用开源解释器时，Skill 要求检查许可证、来源提交、平台假设、所有权模型和语义兼容性。只有相关的上游测试和目标项目回归测试都通过后，才能把复用视为完成。

## 验证

项目模板已经完成 CMake 配置、构建和 CTest 验证。字节码路线也使用适用的《Crafting Interpreters》语言测试进行了前向验证。实现代码或上游测试版本发生变化后，仍应重新确认准确的通过、失败、跳过数量以及各后端的兼容性。

## 许可证

MIT
