<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
        <title>Gaëtan LOLLIERIC</title>
        <link rel="stylesheet" href="css/style.css">
        <link rel="stylesheet" type='text/css' href="https://cdn.jsdelivr.net/gh/devicons/devicon@latest/devicon.min.css" />
        <script src="https://kit.fontawesome.com/db5a202c4a.js" crossorigin="anonymous"></script>
        <script type="text/javascript">
            var letexte = 'Gaëtan LOLLIERIC';
            var cmpt = 0;
           
            function typewriter() {
                let lelien = document.getElementById('titre');
                if (cmpt < letexte.length) {
                    let courant = lelien.innerHTML.substring(0, lelien.innerHTML.length);
                    courant += letexte.charAt(cmpt);
                    lelien.innerHTML = courant;
                    cmpt++;
                    setTimeout(typewriter, 50);
                }
            }

            window.onload = function () {
                typewriter();
            }
        </script>

    </head>
    <body id="home">
        <nav>
            <ul>
                <li><a href="#home"><i class="fa-solid fa-house"></i></a></li>
                <li><a href="#aPropos">A propos</a></li>
                <li><a href="#projets">Projets</a></li>
                <li><a href="#contact"><i class="fa-solid fa-phone"></i></a></li>
            </ul>   
        </nav>
        <header id="#home">
            <div id="textBonjour">
                <img src="images/pp.jpeg"/>
                <h1 id="titre"></h1>
                <p>Bonjour, c'est Gaëtan je suis à la recherche d'une alternance pour mes deux prochaines années de BUT Informatique.</p>
                <a href="fichiers/CV_Gaetan_LOLLIERIC.pdf" download><i class="fa-solid fa-download"></i>Mon CV</a>
            </div>
        </header>
        <section class="smoothscroll gris-container" id="aPropos">
            <div class="aPropos-container">
                <div class="colonne gauche">
                    <img src="images/pp.jpeg"/>
                </div>
                <div class="colonne droite">
                    <div>
                        <h2>À propos de moi</h2>
                        <p>Bonjour, moi c'est Gaëtan LOLLIERIC j'ai 18 ans et je suis actuellement en BUT Informatique à Lannion (22300).
                            J'ai acquis les bases de plusieurs langages de programmation (HTML5, CSS, Java, C, SQL, PHP, Bash). Je suis actuellement à la recherche d'un stage ou d'une alternance en développement web ou logiciel, pour 
                            acquérir de l'expérience professionnelle et développer mon réseau. Je suis plus que motivé pour apprendre en entreprise.</p>
                    </div>
                    <div id="competences">
                        <h2>Mes compétences</h2>
                        <p>Développer des applications informatiques simples<br>
                            Appréhender et construire des algorithmes<br>
                            Installer et configurer un poste de travail<br>
                            Concevoir et mettre en place une base de données à partir d'un cahier des charges client<br>
                            Identifier les besoins métiers des clients et des utilisateurs<br id="contact">
                            Identifier ses aptitudes pour travailler dans une équipe</p>
                    </div>
                    <div>
                        <h2>Contactez moi</h2>
                        <p>Gaëtan LOLLIERIC</p>
                        <p>10 Mez An Avalen Ploumagoar (22970)</p>
                        <p><a href="mailto:gl.lollieric@gmail.com">gl.lollieric@gmail.com</a></p>
                        <p><a href="tel:0768008267">07 68 00 82 67</a></p>
                    </div>
                </div>
            </div>
        </section>
        <section id="monParcour" class="blanc-container">
            <h2>Mon parcours</h2>
            <div class="etudes">
                <div>
                    <h3>BAC Scientifique</h3>
                    <p>Lycée Auguste Pavie, Guingamp (22200)<br>
                    spécialité :</p>
                    <ul>
                        <li>Mathématiques</li>
                        <li>Numérique et Sciences Informatiques</li>
                        <li>Physique Chimie</li>
                    </ul>
                    <p>2021 - 2024</p>
                    <a href="https://www.lycee-pavie.fr/" class="cta">
                        <span class="hover-underline-animation">en savoir plus</span>
                        <svg
                            id="arrow-horizontal"
                            xmlns="http://www.w3.org/2000/svg"
                            width="30"
                            height="10"
                            viewBox="0 0 46 16">
                        <path
                            id="Path_10"
                            data-name="Path 10"
                            d="M8,0,6.545,1.455l5.506,5.506H-30V9.039H12.052L6.545,14.545,8,16l8-8Z"
                            transform="translate(30)">
                        </path>
                        </svg>
                    </a>
                </div>
                <div>
                    <h3>BUT Informatique</h3>
                    <p>IUT de Lannion (22300)</p>
                    <p>2024 - 2025</p>
                    <a href="https://iut-lannion.univ-rennes.fr/" class="cta">
                        <span class="hover-underline-animation">en savoir plus</span>
                        <svg
                            id="arrow-horizontal"
                            xmlns="http://www.w3.org/2000/svg"
                            width="30"
                            height="10"
                            viewBox="0 0 46 16">
                        <path
                            id="Path_10"
                            data-name="Path 10"
                            d="M8,0,6.545,1.455l5.506,5.506H-30V9.039H12.052L6.545,14.545,8,16l8-8Z"
                            transform="translate(30)">
                        </path>
                        </svg>
                    </a>
                    <a href="https://www.enseignementsup-recherche.gouv.fr/sites/default/files/annexe-2-licence-professionnelle-bachelor-universitaire-de-technologie-informatique-29016.pdf" class="cta">
                        <span class="hover-underline-animation">Programme</span>
                        <svg
                            id="arrow-horizontal"
                            xmlns="http://www.w3.org/2000/svg"
                            width="30"
                            height="10"
                            viewBox="0 0 46 16">
                        <path
                            id="Path_10"
                            data-name="Path 10"
                            d="M8,0,6.545,1.455l5.506,5.506H-30V9.039H12.052L6.545,14.545,8,16l8-8Z"
                            transform="translate(30)">
                        </path>
                        </svg>
                    </a>
                </div>
            </div>
        </section>

        <section class="gris-container" id="projets">
            <h2>Mes projets</h2>
            <p>Voici une liste des projets que j'ai réalisé.</p>
            <div class="projets-container">

                <div class="projet-card">
                    <h3>Snake</h3>
                    <img src="images/apercu_snake.jpg"/>
                    <ul>
                        <li><i class="devicon-c-original"></i>C code</li>
                    </ul>
                    <a href="projet.php?pChoose=snake" class="cta">
                        <span class="hover-underline-animation">en savoir plus</span>
                        <svg
                            id="arrow-horizontal"
                            xmlns="http://www.w3.org/2000/svg"
                            width="30"
                            height="10"
                            viewBox="0 0 46 16">
                        <path
                            id="Path_10"
                            data-name="Path 10"
                            d="M8,0,6.545,1.455l5.506,5.506H-30V9.039H12.052L6.545,14.545,8,16l8-8Z"
                            transform="translate(30)">
                        </path>
                        </svg>
                    </a>
                </div>



            
                <div class="projet-card">
                    <h3>Duel de snake automatisé</h3>
                    <img src="images/apercu_snake_auto.jpg"/>
                    <ul>
                        <li><i class="devicon-c-original"></i>C code</li>
                    </ul>   
                    <a href="projet.php?pChoose=duelSnake" class="cta">
                        <span class="hover-underline-animation">en savoir plus</span>
                        <svg
                            id="arrow-horizontal"
                            xmlns="http://www.w3.org/2000/svg"
                            width="30"
                            height="10"
                            viewBox="0 0 46 16">
                        <path
                            id="Path_10"
                            data-name="Path 10"
                            d="M8,0,6.545,1.455l5.506,5.506H-30V9.039H12.052L6.545,14.545,8,16l8-8Z"
                            transform="translate(30)">
                        </path>
                        </svg>
                    </a>
                </div>


                
                <div class="projet-card">
                    <h3>Site web des Jeux Olympiques 2024</h3>
                    <img src="images/apercu_figma.png"/>
                    <ul>
                        <li><i class="fa-brands fa-figma"></i>Figma</li>
                        <li><i class="fa-brands fa-html5"></i>HTLM5</li>
                        <li><i class="fa-brands fa-css3-alt"></i>CSS</li>
                    </ul>
                    <a class="cta" href="projet.php?pChoose=jeuxO">
                        <span class="hover-underline-animation">en savoir plus</span>
                        <svg
                            id="arrow-horizontal"
                            xmlns="http://www.w3.org/2000/svg"
                            width="30"
                            height="10"
                            viewBox="0 0 46 16">
                        <path
                            id="Path_10"
                            data-name="Path 10"
                            d="M8,0,6.545,1.455l5.506,5.506H-30V9.039H12.052L6.545,14.545,8,16l8-8Z"
                            transform="translate(30)">
                        </path>
                        </svg>
                    </a>
                </div>


                <div class="projet-card">
                    <h3>Docker</h3>
                    <img src="images/apercu_docker.jpg"/>
                    <ul>
                        <li><i class="fa-brands fa-docker"></i>Docker</li>
                        <li><i class="fa-solid fa-terminal"></i>Bash</li>
                    </ul>
                    <a href="projet.php?pChoose=docker" class="cta">
                        <span class="hover-underline-animation">en savoir plus</span>
                        <svg
                            id="arrow-horizontal"
                            xmlns="http://www.w3.org/2000/svg"
                            width="30"
                            height="10"
                            viewBox="0 0 46 16">
                        <path
                            id="Path_10"
                            data-name="Path 10"
                            d="M8,0,6.545,1.455l5.506,5.506H-30V9.039H12.052L6.545,14.545,8,16l8-8Z"
                            transform="translate(30)">
                        </path>
                        </svg>
                    </a>
                </div>

                <div class="projet-card">
                    <h3>Base de données</h3>
                    <img src="images/apercu_bdd.jpg"/>
                    <ul>
                        <li><i class="fa-solid fa-database"></i>SQL</li>
                    </ul>
                    <a href="projet.php?pChoose=baseDonnee" class="cta">
                        <span class="hover-underline-animation">en savoir plus</span>
                        <svg
                            id="arrow-horizontal"
                            xmlns="http://www.w3.org/2000/svg"
                            width="30"
                            height="10"
                            viewBox="0 0 46 16">
                        <path
                            id="Path_10"
                            data-name="Path 10"
                            d="M8,0,6.545,1.455l5.506,5.506H-30V9.039H12.052L6.545,14.545,8,16l8-8Z"
                            transform="translate(30)">
                        </path>
                        </svg>
                    </a>
                </div>

                <div class="projet-card">
                    <h3>SEL et RSE de Danone</h3>
                    <img src="images/apercu_danone.jpg"/>
                    <ul>
                        <li><i class="fa-solid fa-magnifying-glass"></i>Recherche</li>
                    </ul>
                    <a href="projet.php?pChoose=danone" class="cta">
                        <span class="hover-underline-animation">en savoir plus</span>
                        <svg
                            id="arrow-horizontal"
                            xmlns="http://www.w3.org/2000/svg"
                            width="30"
                            height="10"
                            viewBox="0 0 46 16">
                        <path
                            id="Path_10"
                            data-name="Path 10"
                            d="M8,0,6.545,1.455l5.506,5.506H-30V9.039H12.052L6.545,14.545,8,16l8-8Z"
                            transform="translate(30)">
                        </path>
                        </svg>
                    </a>
                </div>

                <div class="projet-card">
                    <h3>site web Flask légo</h3>
                    <img src="images/apercu_brik.jpg"/>
                    <ul>
                        <li><i class="fa-brands fa-python"></i>Python</li>
                        <li><i class="fa-brands fa-html5"></i>HTLM5</li>
                        <li><i class="fa-brands fa-css3-alt"></i>CSS</li>
                        <li><i class="fa-solid fa-database"></i>SQL</li>
                    </ul>
                    <a href="projet.php?pChoose=lego" class="cta">
                        <span class="hover-underline-animation">en savoir plus</span>
                        <svg
                            id="arrow-horizontal"
                            xmlns="http://www.w3.org/2000/svg"
                            width="30"
                            height="10"
                            viewBox="0 0 46 16">
                        <path
                            id="Path_10"
                            data-name="Path 10"
                            d="M8,0,6.545,1.455l5.506,5.506H-30V9.039H12.052L6.545,14.545,8,16l8-8Z"
                            transform="translate(30)">
                        </path>
                        </svg>
                    </a>
                </div>

                <div class="projet-card">
                    <h3>Space Invaders</h3>
                    <img src="images/apercu_spaceInvador.jpg"/>
                    <ul>
                        <li><i class="fa-brands fa-python"></i>Python</li>
                    </ul>
                    <a href="projet.php?pChoose=spaceInvador" class="cta">
                        <span class="hover-underline-animation">en savoir plus</span>
                        <svg
                            id="arrow-horizontal"
                            xmlns="http://www.w3.org/2000/svg"
                            width="30"
                            height="10"
                            viewBox="0 0 46 16">
                        <path
                            id="Path_10"
                            data-name="Path 10"
                            d="M8,0,6.545,1.455l5.506,5.506H-30V9.039H12.052L6.545,14.545,8,16l8-8Z"
                            transform="translate(30)">
                        </path>
                        </svg>
                    </a>
                </div>
            </div>

        </section>

        <footer class="site-footer">
            <div class="footer-container">
                <div class="footer-section">
                <h4>Contact</h4>
                <p>Email : <a href="mailto:gl.lollieric@gmail.com">gl.lollieric@gmail.com</a></p>
                <p>Téléphone : <a href="tel:0768008267">07 68 00 82 67</a></p>
                </div>

                <div class="footer-section">
                <h4>Suivez-moi</h4>
                <div class="social-icons">
                    <a href="https://fr.linkedin.com/in/ga%C3%ABtan-lollieric-6aa34a356" target="_blank"><i class="fa-brands fa-linkedin"></i></a>
                    <a href="https://github.com/Wirohx/" target="_blank"><i class="fa-brands fa-github"></i></a>
                    <a href="https://www.instagram.com/gaetan_lollieric/" target="_blank"><i class="fa-brands fa-instagram"></i></a>
                </div>
            </div>
            <div class="footer-bottom">
                <p>&copy; 2025 Gaëtan LOLLIERIC. Tous droits réservés.</p>
            </div>
        </footer>
    </body>
</html>
