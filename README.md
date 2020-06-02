# man_world pseudo game  
??sudo apt-get install libsdl-image1.2-dev
sudo apt-get install libsdl2-dev
sudo apt install libsdl2-image-dev

mkdir build  
cd build  
cmake ..  
cd build  
make  
./man_world {config_path{../config/default_config.json}}