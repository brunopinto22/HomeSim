cmake_minimum_required(VERSION 3.23)
project(HomeSim)

set(CMAKE_CXX_STANDARD 20)

add_executable(HomeSim
        main.cpp curses.h
        Terminal.h Terminal.cpp
        Habitacao/Comando.cpp Habitacao/Comando.h
        Habitacao/Habitacao.cpp Habitacao/Habitacao.h
        Habitacao/Zona.cpp Habitacao/Zona.h
        Habitacao/Propriedade.cpp Habitacao/Propriedade.h
        Habitacao/Componentes/Sensor.cpp Habitacao/Componentes/Sensor.h
        Habitacao/Componentes/Regra.cpp Habitacao/Componentes/Regra.h
        Habitacao/Componentes/Processador.cpp Habitacao/Componentes/Processador.h
        Habitacao/Componentes/Aparelho.cpp Habitacao/Componentes/Aparelho.h
        Habitacao/Componentes/Componente.cpp Habitacao/Componentes/Componente.h
        Simulador.cpp Simulador.h)

target_link_libraries(${PROJECT_NAME} C:/Users/HP/Desktop/Bruno/4.Documentos/1.Escola/Uni/2Ano/1Semestre/POO/1.TP/PDCurses-3.9/wincon/pdcurses.a)