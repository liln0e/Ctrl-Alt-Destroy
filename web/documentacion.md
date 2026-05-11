---
layout: page
title: Documentación
---

# Documentación del proyecto

En esta sección se recoge la información técnica relacionada con el diseño mecánico, electrónico y software del robot desarrollado por el equipo **Ctrl+Alt+Destroy**.

---

# Diseño mecánico

## Estructura general

El robot utiliza un chasis diseñado mediante modelado e impresión 3D, pensado para integrar de forma compacta los elementos electrónicos y mecánicos necesarios para su funcionamiento.

La estructura incluye:

- Chasis principal impreso en 3D.
- Tapa superior impresa en 3D.
- Soporte para PCB y componentes electrónicos.
- Sistema de tracción mediante motores.
- Espacio para batería, sensores y cableado.

## Archivos mecánicos

En el repositorio se incluyen los siguientes archivos relacionados con el diseño mecánico:

- `chasis_sumo_bot.3mf` → Modelo 3D original del chasis descargado y adaptado para el proyecto.
- `chasis_sumo_bot.gcode.3mf` → Archivo preparado para la impresión 3D del chasis.
- `tapa.3mf` → Modelo 3D de la tapa superior del robot.
- `tapa.gcode.3mf` → Archivo preparado para la impresión 3D de la tapa.

## Proceso de construcción

El chasis ha sido fabricado mediante **impresión 3D en la universidad**, lo que permitió reducir costes y adaptar el diseño a las necesidades del proyecto.

Durante el montaje fue necesario realizar algunas modificaciones respecto al diseño inicial:

- Se realizaron agujeros adicionales para adaptar correctamente la fijación de los tornillos de los motores, ya que las medidas iniciales no coincidían completamente.
- Se modificó la conexión del sensor encargado de detectar el suelo, conectándolo al pin **GPIO 34** de la **ESP32**, debido a problemas de detección durante las pruebas.

El objetivo del diseño mecánico es conseguir una estructura ligera, estable y resistente que permita alojar correctamente la electrónica, motores, batería y sensores.

**Responsable principal:** Brais Maciñeiras Pena.

---

# Diseño electrónico

## Objetivo

La parte electrónica del robot se centra en el diseño y fabricación de una PCB propia para integrar los componentes necesarios para el funcionamiento del robot.

La placa ha sido diseñada utilizando **KiCad**, permitiendo organizar las conexiones eléctricas, distribuir los componentes y facilitar el ensamblaje del sistema.

## Elementos principales

La electrónica del robot incluye:

- Microcontrolador **ESP32**.
- Sensores para detección del entorno y del suelo.
- Conexiones para motores y alimentación.
- PCB personalizada diseñada para el proyecto.
- Conectores y componentes auxiliares para el montaje.

## Archivos electrónicos

Dentro del repositorio se incluyen los siguientes archivos relacionados con el diseño electrónico:

- `sumo_robot.kicad_sch` → Esquemático electrónico del circuito.
- `sumo_robot.kicad_pcb` → Diseño de la PCB.
- `sumo_robot.kicad_pro` → Archivo del proyecto de KiCad.

Estos archivos permiten revisar, modificar y fabricar de nuevo la placa si fuese necesario.

Las imágenes del diseño y fabricación de la PCB pueden consultarse en el apartado **Fotos y vídeos**.

**Responsable principal:** Carmen Sestelo Arias.

---

# Diseño de software

## Objetivo

El software del robot se encarga de gestionar el comportamiento general del sistema, incluyendo el control del movimiento y la interacción entre sensores, motores y componentes electrónicos.

## Archivo principal

En la carpeta `software/` se incluye el archivo:

- `sumo_robot_final.ino` → Código principal del robot.

## Funcionalidades

El código permite controlar distintas funciones del robot, entre ellas:

- Control del movimiento.
- Lectura y gestión de sensores.
- Coordinación entre sensores, motores y electrónica.
- Pruebas y ajustes del comportamiento del robot.

El código ha sido desarrollado y ajustado durante el proceso de construcción del robot.

**Responsables:** Carmen Sestelo Arias y Brais Maciñeiras Pena.

---

# Comunicación, documentación y web

La documentación del proyecto y la página web del equipo sirven para mostrar el progreso del robot, organizar la información técnica y presentar el trabajo realizado.

Esta parte incluye:

- Gestión del repositorio.
- Organización de la documentación.
- Desarrollo de la web del proyecto.
- Presentación visual del equipo y del robot.

**Responsable principal:** Noelia Castro Rodríguez.

---

# Organización del repositorio

El proyecto está organizado en distintas carpetas para facilitar el trabajo colaborativo y la documentación:

```txt
electronica/
mecanica/
software/
web-proyecto/
```

- **electronica/** → Diseño PCB y documentación electrónica.
- **mecanica/** → Modelado, chasis y diseño estructural del robot.
- **software/** → Código del robot y lógica de funcionamiento.
- **web-proyecto/** → Página web y documentación visual del proyecto.