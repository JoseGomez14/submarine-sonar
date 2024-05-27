"use client";

import { useEffect, useState } from "react";

import { socket } from "../services/sonar";

export default function Radar() {
  const MAX_DISTANCE = process.env.NEXT_PUBLIC_MAX_SENSOR_DISTANCE || 150;
  const PI = Math.PI;
  const WS_CONNECTION_URL = process.env.NEXT_PUBLIC_SERVER_URL_WS;

  const radarCircles = [0.25, 0.5, 0.75, 1];

  const [radarLineOptions, setRadarLineOptions] = useState({});
  const [radarData, setRadarData] = useState({});
  const [radarPoints, setRadarPoints] = useState({});

  useEffect(() => {
    let windowWidth = 0;
    let windowHeight = 0;
    if (typeof window !== "undefined") {
      windowWidth = window?.innerWidth / 2 - (window.innerWidth / 2) * 0.1;
      windowHeight = window?.innerHeight - window.innerHeight * 0.1;
    }

    setRadarLineOptions({
      width: windowHeight < windowWidth ? windowHeight : windowWidth,
      height: 5,
      color: "#00ff26",
    });

    socket.on(WS_CONNECTION_URL, (data) => {
      let { position, distance } = data;
      setRadarData({
        position: parseInt(position),
        distance: parseInt(distance),
      });
    });
  }, []);

  useEffect(() => {
    if (radarData.distance !== -1) {
      const radarPoint = {
        x:
          ((radarData.distance * Math.cos((radarData.position * PI) / 180)) /
            MAX_DISTANCE) *
          radarLineOptions.width,
        y:
          ((radarData.distance * Math.sin((radarData.position * PI) / 180)) /
            MAX_DISTANCE) *
          radarLineOptions.width,
      };

      setRadarPoints({
        ...radarPoints,
        [radarData.position]: radarPoint,
      });
    } else {
      delete radarPoints[radarData.position];
    }
  }, [radarData]);

  return (
    <div className="radar">
      <div
        className="radar__scan"
        style={{
          width: radarLineOptions.width * 2,
          height: radarLineOptions.width,
          display: "flex",
          justifyContent: "start",
          alignItems: "end",
        }}
      >
        <div
          className="radar__scan__line"
          style={{
            transform: `rotate(${-1 * radarData.position + 180}deg)`,
            background: radarLineOptions.color,
            width: radarLineOptions.width,
            height: radarLineOptions.height,
            transformOrigin: `${radarLineOptions.width}px 
            ${radarLineOptions.height / 2}px`,
            boxShadow: `0 0 25px ${radarLineOptions.color}`,
          }}
        ></div>
      </div>

      {Object.keys(radarPoints).map((key, index) => (
        <div
          key={index}
          className="radar__point"
          style={{
            position: "fixed",
            width: "1rem",
            height: "1rem",
            background: radarLineOptions.color,
            top: `calc(100vh - 1rem - ${radarPoints[key].y}px)`,
            left: `calc(50vw + ${radarPoints[key].x}px - 0.5rem)`,
            borderRadius: "50%",
            boxShadow: `0 0 2rem ${radarLineOptions.color}55`,
          }}
        ></div>
      ))}

      <div
        className="radar__circule__central"
        style={{
          position: "fixed",
          width: "2rem",
          height: "2rem",
          borderRadius: "50%",
          background: radarLineOptions.color,
          top: `calc(100vh - 1rem)`,
          left: `calc(50vw - 1rem)`,
        }}
      ></div>

      {radarCircles.map((circle, index) => (
        <div
          key={index}
          className="radar__circle"
          style={{
            position: "fixed",
            width: radarLineOptions.width * 2 * circle,
            height: radarLineOptions.width * 2 * circle,
            borderRadius: "50%",
            border: `1px solid ${radarLineOptions.color}`,
            top: `calc(100vh - 10px - ${radarLineOptions.width * circle}px)`,
            left: `calc(50vw - ${radarLineOptions.width * circle}px)`,
            boxShadow: `0 0 3rem ${radarLineOptions.color}33 inset`,
          }}
        >
          <span
            style={{
              position: "absolute",
              top: "50%",
              left: "0.25rem",
              transform: "translateY(-60%)",
              color: "white",
              fontWeight: "bold",
            }}
          >
            {MAX_DISTANCE * circle} cm
          </span>
        </div>
      ))}
    </div>
  );
}