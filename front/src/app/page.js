import Radar from "../components/Radar";
import styles from "./page.module.css";

export default function Home() {
  return (
    <main className={styles.main}>
      <Radar />
    </main>
  );
}
