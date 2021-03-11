# Code style
## C++
### General
* Mostly no macros allowed. Use `constexpr` instead
* No include guards allowed, `#pragma once` is used instead
* Name spaces don't indent code
* No `using namespace` allowed
* Code should be formatted using `clang-format`
* Spaces are used instead of tabs all the time

### File names
#### Headers
* Header _files_ are put in the `include` directory
* Header _filenames_ end with **.hh**
* Header _filenames_ follow the **snake_case** style

#### Sources
* Source _files_ are put in the `src` directory
* Source _filenames_ end with **.cc**
* Source _filenames_ follow the **snake_case** style

### Naming
* _Variables_ and _name spaces_ follow the **snake_case** style
* _Constants_ follow the **SCREAMING_SNAKE_CASE** style
* _Type aliases_ follow the **snake_case** style
* _Class names_ follow the **PascalCase** style
* _Structure names_ follow the **snake_case** style
* _Function_ and _method names_ follow the **camelCase** style

### Brace wrapping
Opening braces are placed on the next line for:

* Name spaces
* Functions
* Scopes

### Include blocks
Headers are sorted in alphabetical order regardless of the subdirectory:

* Headers that belong to the project _itself_ must be placed in the first block
* Headers that doesn't belong to the project (_standard_ or _third-party_) must be placed in the second block

## HLSL
### General
* Almost all C++ rules apply also for HLSL except for some
* Macros are allowed (does HLSL even have `constexpr`?)
* There is no `clang-format` for shaders so format it manually.

### File names
#### Sources
* Shader source _files_ are put in the `shaders` directory
* Shader source _filenames_ end with **.hlsl**
* Shader source _filenames_ follow the **snake_case** style
* Shader source _filenames_ have the sub-extension defining its stage:
  * Vertex: `vert`
  * Fragment: `frag`

#### Binaries
* Shader binary _files_ are put in the `shaders` directory
* Shader binary _filenames_ end with **.spv**
* Shader binary _filenames_ follow the same naming rules as the _shader sources_
