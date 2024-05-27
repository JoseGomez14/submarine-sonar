import styles from "./styles/radarinfo.module.css";

const RadarInfo = ({ radarData, plotObjects, setPlotObjects, objects }) => {
  const closestObject = Object.values(objects).reduce((acc, curr) => {
    if (acc === null) return curr;
    return curr.distance < acc.distance ? curr : acc;
  }, null);

  return !plotObjects ? (
    <div className="radar__info">
      <h2>Información</h2>
      <div className="radar__info__item">
        <span>Ángulo: </span>
        <span>{radarData.position}°</span>
      </div>
      <div className="radar__info__item">
        <span>Distancia: </span>
        <span>
          {radarData.distance == -1 ? "Sin obstaculos" : radarData.distance}
        </span>
      </div>
      <div className="radar__info__item">
        <span>Sentido: </span>
        <span>{radarData.direction == -1 ? "Horario" : "Antiohorario"}</span>
      </div>
      <button
        className={styles.modeSelector}
        onClick={() => setPlotObjects(true)}
        title="Mostrar obstaculos"
      >
        <svg
          xmlns="http://www.w3.org/2000/svg"
          width={24}
          height={24}
          viewBox="0 0 24 24"
          fill="none"
          stroke="currentColor"
          strokeWidth={2}
          strokeLinecap="round"
          strokeLinejoin="round"
        >
          <path d="M0 0h24v24H0z" stroke="none" />
          <path d="M4 8V6a2 2 0 012-2h2M4 16v2a2 2 0 002 2h2M16 4h2a2 2 0 012 2v2M16 20h2a2 2 0 002-2v-2M8 10a2 2 0 012-2h4a2 2 0 012 2v4a2 2 0 01-2 2h-4a2 2 0 01-2-2z" />
        </svg>
      </button>
    </div>
  ) : (
    <div className="radar__info">
      <h2>Información</h2>

      <div className="radar__info__item">
        <span>Obstaculos: </span>
        <span>
          {Object.keys(objects).length > 0 ? Object.keys(objects).length : 0}
        </span>
      </div>
      <div className="radar__info__item">
        <span>Obstaculo más cerano: </span>
        <span>
          {closestObject
            ? `${parseInt(closestObject.distance)} cm`
            : "No hay obstaculo"}
        </span>
      </div>
      <div className="radar__info__item">
        <span>Tamño del obstaculo: </span>
        <span>
          {closestObject
            ? `${(closestObject.width)} cm`
            : "No hay obstaculo"}
        </span>
      </div>
      <button
        className={styles.modeSelector}
        onClick={() => setPlotObjects(false)}
        title="Mostrar puntos"
      >
        <svg
          xmlns="http://www.w3.org/2000/svg"
          width={24}
          height={24}
          viewBox="0 0 24 24"
          fill="none"
          stroke="currentColor"
          strokeWidth={2}
          strokeLinecap="round"
          strokeLinejoin="round"
        >
          <path d="M0 0h24v24H0z" stroke="none" />
          <path d="M3.5 9.5a1 1 0 102 0 1 1 0 10-2 0M8.5 4.5a1 1 0 102 0 1 1 0 10-2 0M8.5 14.5a1 1 0 102 0 1 1 0 10-2 0M3.5 19.5a1 1 0 102 0 1 1 0 10-2 0M13.5 9.5a1 1 0 102 0 1 1 0 10-2 0M18.5 4.5a1 1 0 102 0 1 1 0 10-2 0M13.5 19.5a1 1 0 102 0 1 1 0 10-2 0M18.5 14.5a1 1 0 102 0 1 1 0 10-2 0" />
        </svg>
      </button>
    </div>
  );
};

export default RadarInfo;
