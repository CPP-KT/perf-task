# perf

В этой задаче вам дан набор бенчмарков. В каждом бенчмарке есть performance bug.

Вы должны найти и исправить этот баг, **используя профайлер perf**. Менять
алгоритм запрещается!

 - `bench_jpeg` - найти bottleneck и ускорить бенчмарк в 6 раз.
 - `bench_pi` - найти bottleneck и ускорить бенчмарк в 20 раз.
 - `bench_radix_sort` - найти bottleneck и ускорить бенчмарк на 40%.
 - `bench_json` - понять что тормозит и ускорить бенчмарк на 40%.
 - `bench_logger` - найти bottleneck и ускорить бенчмарк в 8 раз. Смысл класса Logger должен остаться прежним. После завершения процесса содержимое лога должно быть таким же как и до ваших изменений.

Не забудьте, что профилировать нужно релизную сборку кода c включенными дебажными символами (`--preset RelWithDebInfo` при сборке с vcpkg).

Профайлер нужно использовать в режиме `record && report`. Режим `stat` в этой задаче вам не поможет.

Возможно вам помогут флаги `-g` и `--call-graph dwarf`.

## Сборка и профилирование
### Системы, отличные от Linux
> :warning: **Работоспособность гарантируется только на Linux**, на остальных системах рекомендуется использовать докер или любую другую виртуалку, на Windows в качестве виртуалки подойдёт WSL.

Чтобы запускать всё в docker, можно использовать инструкцию [отсюда](https://github.com/CPP-KT/dev-tools), в образе уже есть весь тулинг. \
Чтобы работал perf внутри докера, нужно добавить `--privileged` к docker run. \
Итоговая команда запуска будет выглядеть как-то так:
```
docker run --privileged -t -v ~/perf-lejabque:/perf-lejabque -i clang-remote-dev /bin/bash
```

### Сборка руками
В этой задаче как обычно работает сборка и запуск [через CLion](https://cpp-kt.github.io/course/ide/clion.html), но возможностей встроенного в CLion профайлера вам может не хватить.

Чтобы собрать руками, можно выполнить следующие команды (при условии, что у вас уже настроено окружение аналогичное тому, что для запуска через clion, то есть установлен vcpkg).
```
mkdir -p cmake-build-RelWithDebInfo
rm -rf cmake-build-RelWithDebInfo/*
cmake "-DCMAKE_TOOLCHAIN_FILE=<path-to-vcpkg>/vcpkg/scripts/buildsystems/vcpkg.cmake" -GNinja --preset RelWithDebInfo -S .
cmake --build cmake-build-RelWithDebInfo
```
Бинари для каждой из подзадач будут лежать в `cmake-build-RelWithDebInfo/perf`, дальше их можно использовать для запуска под perf.

Полезное про perf: https://www.brendangregg.com/perf.html
