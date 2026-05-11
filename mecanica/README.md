# Diseño mecánico del robot

En esta carpeta se incluye la documentación mecánica necesaria para la construcción del robot BattleBot del equipo **Ctrl+Alt+Destroy**.

## Contenido

Los siguientes archivos corresponden al diseño e impresión del chasis del robot:

- `chasis_sumo_bot.3mf` → Modelo 3D original del chasis descargado y adaptado para el proyecto.
- `chasis_sumo_bot.gcode.3mf` → Archivo preparado para la impresión 3D del chasis.
- `tapa.3mf` → Modelo 3D de la tapa superior del robot.
- `tapa.gcode.3mf` → Archivo preparado para la impresión 3D de la tapa.

## Diseño mecánico

La parte mecánica del robot se centra en el diseño del chasis, la estructura y la adaptación de componentes para garantizar estabilidad, resistencia y un correcto ensamblaje del sistema.

El chasis ha sido fabricado mediante **impresión 3D en la universidad**, permitiendo reducir costes de fabricación y adaptar el diseño a las necesidades del proyecto.

Durante el proceso de construcción fue necesario realizar algunas modificaciones respecto al diseño inicial:

- Se realizaron agujeros adicionales para adaptar correctamente la fijación de los tornillos de los motores, ya que las medidas iniciales no coincidían completamente.
- Se ajustó la conexión del sensor encargado de detectar el suelo, modificando el pin utilizado en la **ESP32** al **GPIO 34**, debido a problemas de detección durante las pruebas.

El diseño mecánico busca integrar de forma compacta la electrónica, motores, batería y sensores, manteniendo un tamaño reducido y una estructura funcional para el robot.

## Extra: decoración del robot

Una vez terminado el robot, **Noelia Castro Rodríguez** también se encargó de decorarlo, pintándolo y añadiendo pegatinas para darle personalidad propia. Aunque no sea especialmente profesional ni técnicamente relevante, hace que el robot sea bastante más gracioso, memorable y con mucho más estilo.

**Responsable principal del diseño mecánico:** Brais Maciñeiras Pena.