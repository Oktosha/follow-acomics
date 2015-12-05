#follow-acomics

Это консольное приложение позволяет следить, сколько новых выпусков выбранных комиксов появилось на acomiсs.

#как запустить

Итак, вы склонировали этот репозиторий командой

```
git clone https://github.com/Oktosha/follow-acomics.git
```

Теперь нужно добавить библиотеку casablanca. 
Для начала необходимо поставить библиотеки, от которых она зависит. Проще всего это сделать с помощью менеджера пакетов [brew](http://brew.sh/).

```
brew install cmake git openssl boost libiconv
```

Теперь скачайте эту библиотеку casablanca (она же cpprest) в папку casablanca внутри проекта. Важно, чтобы название папки было именно casablanca.

```
cd follow-acomics
git clone https://github.com/Microsoft/cpprestsdk.git casablanca
```

После этого соберите casablanca в поддиректории build.relase

```
cd casablanca
mkdir build.release
cd build.release
cmake ../Release -DCMAKE_BUILD_TYPE=Release
make install
```

Сборка будет довольно долгой. В итоге структура проекта должна получится такой:

```
follow-acomics
├── [исходники приложения]
└── casablanca
    ├── [исходники casablanca]
    └── build.release
         └── [собранная библиотека casablanca]
```

Теперь перейдите в корень проекта follow-acomics и соберите само приложение

```
cd ../..
make
```

Запустите приложение

```
./follow-acomics
```