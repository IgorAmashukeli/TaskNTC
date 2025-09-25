Установите С++ библиотеки cpr (зависит от libcurl), crow, icu

То есть должны быть подкдючены глобально следующие файлы:

`<crow.h>`

`<cpr/cpr.h>`

`<unicode/brkiter.h>`

`<unicode/unistr.h>`

`<unicode/utypes.h>`

Заполните файл text.txt текстом и скомпилируйте

`clang++ --std=c++20 server.cpp str_utils.cpp -licuuc -licuio -o server`

`clang++ --std=c++20 client.cpp -lcpr -lcurl -o client`

Запустите

`./server`

Затем можно сколько угодно раз запускать `/.client` - в выводе будет нужный json
