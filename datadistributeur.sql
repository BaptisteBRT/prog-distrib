-- phpMyAdmin SQL Dump
-- version 4.6.6deb5ubuntu0.5
-- https://www.phpmyadmin.net/
--
-- Client :  localhost:3306
-- Généré le :  Lun 27 Juin 2022 à 20:43
-- Version du serveur :  5.7.38-0ubuntu0.18.04.1
-- Version de PHP :  7.2.24-0ubuntu0.18.04.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de données :  `datadistributeur`
--

-- --------------------------------------------------------

--
-- Structure de la table `Animaux`
--

CREATE TABLE `Animaux` (
  `idAnimal` int(11) NOT NULL,
  `nom` varchar(15) DEFAULT NULL,
  `tag` varchar(60) NOT NULL,
  `poids` int(11) DEFAULT NULL,
  `age` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Contenu de la table `Animaux`
--

INSERT INTO `Animaux` (`idAnimal`, `nom`, `tag`, `poids`, `age`) VALUES
(2, 'Gipsy', '123', 0, 0);

-- --------------------------------------------------------

--
-- Structure de la table `Croquettes`
--

CREATE TABLE `Croquettes` (
  `idCroquette` int(11) NOT NULL,
  `nom` varchar(15) NOT NULL,
  `actif` tinyint(1) NOT NULL,
  `qteParSec` float NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Contenu de la table `Croquettes`
--

INSERT INTO `Croquettes` (`idCroquette`, `nom`, `actif`, `qteParSec`) VALUES
(1, 'diet', 1, 3);

-- --------------------------------------------------------

--
-- Structure de la table `Programme`
--

CREATE TABLE `Programme` (
  `idProgramme` int(11) NOT NULL,
  `idAnimal` int(11) NOT NULL,
  `idCroquette` int(11) NOT NULL,
  `heure` time NOT NULL,
  `quantite` float NOT NULL,
  `distribue` tinyint(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Contenu de la table `Programme`
--

INSERT INTO `Programme` (`idProgramme`, `idAnimal`, `idCroquette`, `heure`, `quantite`, `distribue`) VALUES
(1, 2, 1, '06:00:00', 10, 0),
(2, 2, 1, '10:00:00', 15, 0),
(10, 2, 1, '14:00:00', 20, 0),
(11, 2, 1, '19:00:00', 10, 0);

-- --------------------------------------------------------

--
-- Structure de la table `Repas`
--

CREATE TABLE `Repas` (
  `idRepas` int(11) NOT NULL,
  `date` datetime NOT NULL,
  `quantite` float NOT NULL,
  `idAnimal` int(11) NOT NULL,
  `idCroquette` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Contenu de la table `Repas`
--

INSERT INTO `Repas` (`idRepas`, `date`, `quantite`, `idAnimal`, `idCroquette`) VALUES
(22, '2022-06-24 17:52:33', 25, 2, 1),
(23, '2022-06-27 15:23:20', 10, 2, 1),
(24, '2022-06-27 15:24:11', 25, 2, 1),
(25, '2022-06-27 19:00:58', 25, 2, 1);

--
-- Index pour les tables exportées
--

--
-- Index pour la table `Animaux`
--
ALTER TABLE `Animaux`
  ADD PRIMARY KEY (`idAnimal`);

--
-- Index pour la table `Croquettes`
--
ALTER TABLE `Croquettes`
  ADD PRIMARY KEY (`idCroquette`);

--
-- Index pour la table `Programme`
--
ALTER TABLE `Programme`
  ADD PRIMARY KEY (`idProgramme`);

--
-- Index pour la table `Repas`
--
ALTER TABLE `Repas`
  ADD PRIMARY KEY (`idRepas`),
  ADD KEY `idAnimal` (`idAnimal`),
  ADD KEY `idCroquette` (`idCroquette`);

--
-- AUTO_INCREMENT pour les tables exportées
--

--
-- AUTO_INCREMENT pour la table `Animaux`
--
ALTER TABLE `Animaux`
  MODIFY `idAnimal` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=22;
--
-- AUTO_INCREMENT pour la table `Croquettes`
--
ALTER TABLE `Croquettes`
  MODIFY `idCroquette` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;
--
-- AUTO_INCREMENT pour la table `Programme`
--
ALTER TABLE `Programme`
  MODIFY `idProgramme` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=12;
--
-- AUTO_INCREMENT pour la table `Repas`
--
ALTER TABLE `Repas`
  MODIFY `idRepas` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=29;
--
-- Contraintes pour les tables exportées
--

--
-- Contraintes pour la table `Repas`
--
ALTER TABLE `Repas`
  ADD CONSTRAINT `Repas_ibfk_1` FOREIGN KEY (`idAnimal`) REFERENCES `Animaux` (`idAnimal`) ON UPDATE CASCADE,
  ADD CONSTRAINT `Repas_ibfk_2` FOREIGN KEY (`idCroquette`) REFERENCES `Croquettes` (`idCroquette`) ON UPDATE CASCADE;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
