<div align="center">
<h1>Sonar para submarinos 🤖🔈</h1>
<h2>Este proyecto se basa en la construcción de un sonar para submarinos aplicando IoT, desarrollo Web y aplicaciones de física de ondas.</h2>

<h2><a href='https://submarine-sonar.vercel.app/'>WEB</a> | <a href='/'>DEMO</a> </h2>
</div>
El sonar es un dispositivo que emite ondas sonoras y recibe las ondas reflejadas por los objetos que se encuentran en el agua. A partir de la información recibida, se puede determinar la distancia a la que se encuentra el objeto y su tamaño.

![Mockup-WEB-sonar](https://github.com/JoseGomez14/submarine-sonar/assets/110755221/76b121ee-aed4-4eac-a269-353a874b6a2d)

## Integrantes

Se desarrolló por un grupo de estudiantes de la Universidad de Antioquia, del programa de Ingeniería de Sistemas, en el curso de Laboratorio Integrado de Ondas, durante el semestre 2024-1.

- [Jose David Gómez](https://github.com/josegomez14)
- [Daniel Lujan](https://github.com/daniel-lujan)
- [Emanuel López](https://github.com/emanuellopezh)

Además, contamos con la colaboración del profesor encargado del Laboratiorio Integreado de Ondas, Victor Navarro.

## Tecnologías

- [Arduino](https://www.arduino.cc/)
- [Node.js](https://nodejs.org/)
- [Socket.io](https://socket.io/)
- [Next.js](https://nextjs.org/)

## Instalación y ejecución local

1. Clonar el repositorio

```bash
git clone https://github.com/JoseGomez14/submarine-sonar.git
```

2. Controlador del Arduino

El código que se encuentra en la carpeta `/IoT` debe ser cargado en el Arduino. Para ello, se debe tener instalado el IDE de Arduino y seleccionar el puerto COM correspondiente. Además, se debe tener en cuenta que el Arduino debe estar conectado al sensor de ultrasonido como se muestra en el [esquema de conexión](#esquema-de-conexión-del-arduino).

> [!NOTE]
> El código está pensado para un Arduino Uno o Nano, y sensor de ultrasonido HC-SR04. Si se desea utilizar otro modelo de Arduino o sensor, se deben realizar las modificaciones necesarias. 

3. Servidor Local

El servidor local se encuentra en la carpeta `/IoT/server`. Para ejecutarlo, se debe instalar las dependencias y ejecutar el servidor.

> [!NOTE]  
> En el archivo `/IoT/server/.env.development` se encuentra la configuración del puerto en el que se ejecutará el servidor y el puerto del socket que debe coincidir con el puerto configurado en el Arduino.


```bash
cd IoT/server
npm install
npm run dev
```

> [!IMPORTANT]  
> Es necesario tener instalado Node.js en el equipo, conectar el Arduino al puerto COM y tener el serial monitor cerrado.

4. Servidor Backend

El servidor backend se encuentra en la carpeta `/back`. Para ejecutarlo, se debe instalar las dependencias y ejecutar el servidor.

```bash
cd back
npm install
npm run dev
```

> [!NOTE]
> Este servidor se encarga de recibir los datos enviados por el servidor local y enviarlos a los clientes conectados.

5. Cliente Web

El cliente web se encuentra en la carpeta `/front`. Para ejecutarlo, se debe instalar las dependencias y ejecutar el servidor.

```bash
cd front
npm install
npm run dev
```

> [!TIP]
> De esta forma, se podrá acceder a la aplicación web en la dirección `http://localhost:3000`.

## Esquema de conexión del Arduino

![esquema](https://github.com/JoseGomez14/submarine-sonar/assets/110755221/0959d2f5-215f-455f-bcce-5dc5f436027f)