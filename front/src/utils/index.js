export const calcObjects = (points, direction, radarLineOptions) => {
  const MIN_POINTS = 7; // Mínimo de puntos para ser considerado un objeto
  const MAX_DISTANCE = parseInt(
    process.env.NEXT_PUBLIC_MAX_SENSOR_DISTANCE ?? 150
  );
  const EPSILON = 0.2 * MAX_DISTANCE;
  const PI = Math.PI;
  const objects = {};

  let pointCounter = 0;
  let distanceSum = 0;
  let prevDistance = null;

  const addObject = (angle, avgDistance) => {
    if (pointCounter >= MIN_POINTS) {
      const w =
        2 * avgDistance * Math.tan((PI * (pointCounter - 1 - 7.5)) / 180);
      // console.log({ pointCounter, w, angle });
      console.log(objects);
      const x =
        ((avgDistance *
          Math.cos(((angle - (pointCounter - 1 * direction)) * PI) / 180)) /
          MAX_DISTANCE) *
        radarLineOptions.width;
      const y =
        ((avgDistance *
          Math.sin(((angle - (pointCounter - 1 * direction)) * PI) / 180)) /
          MAX_DISTANCE) *
        radarLineOptions.width;
      objects[angle] = {
        width: w,
        x,
        y,
      };
    }
    // console.log(objects);
    pointCounter = 0;
    distanceSum = 0;
  };

  for (let angle = 0; angle <= 180; angle += 2) {
    if (!points[angle]) {
      const avgDistance = distanceSum / pointCounter;
      addObject(angle, avgDistance);
      continue;
    }
    const distance = points[angle].distance;
    if (Math.abs(distance - prevDistance) < EPSILON) {
      pointCounter++;
      distanceSum += distance;
    } else {
      const avgDistance = distanceSum / pointCounter;
      addObject(angle, avgDistance);
    }

    prevDistance = distance;
  }

  if (pointCounter >= MIN_POINTS) {
    addObject(180, distanceSum / pointCounter);
  }

  return objects;
};
