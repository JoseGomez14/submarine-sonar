import Navbar from "@/components/Navbar";
import Radar from "../components/Radar";
import styles from "./page.module.css";

export default function Home() {
  return (
    <>
      <header className={styles.header}>
        <Navbar />
      </header>
      <main className={styles.main}>
        <Radar />
      </main>
    </>
  );
}
