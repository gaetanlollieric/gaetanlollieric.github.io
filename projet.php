<html>
    <header>
        <link rel="stylesheet" href="css/styleProjet.css" />
        <link rel="stylesheet" type='text/css' href="https://cdn.jsdelivr.net/gh/devicons/devicon@latest/devicon.min.css" />
        <script src="https://kit.fontawesome.com/db5a202c4a.js" crossorigin="anonymous"></script>   
    </header>
    <body>
        
        <nav>
            <ul>
                <li><a href="index.php"><i class="fa-solid fa-house"></i></a></li>
                <li><a href="index.php#contact"><i class="fa-solid fa-phone"></i></a></li>
            </ul>   
        </nav>
        <?php
            function quelleCompetence($data){
                $lesCompetences = "<ul>";
                
                if ($data[5]==1){
                    $lesCompetences = $lesCompetences . "<li>Python</li>";
                }

                if ($data[6]==1){
                    $lesCompetences = $lesCompetences . "<li><i class='fa-brands fa-css3-alt'></i>CSS</li>";
                }

                if ($data[7]==1){
                    $lesCompetences = $lesCompetences . "<li><i class='fa-brands fa-html5'></i>HTML</li>";
                }

                if ($data[8]==1){
                    $lesCompetences = $lesCompetences . "<li><i class='fa-brands fa-docker'></i>Docker</li>";
                }

                if ($data[9]==1){
                    $lesCompetences = $lesCompetences . "<li><i class='fa-solid fa-terminal'></i>Bash</li>";
                }

                if ($data[10]==1){
                    $lesCompetences = $lesCompetences . "<li><i class='devicon-c-original'></i>C code</li>";
                }

                if ($data[11]==1){
                    $lesCompetences = $lesCompetences . "<li><i class='fa-solid fa-database'></i>SQL</li>";
                }

                if ($data[12]==1){
                    $lesCompetences = $lesCompetences . "<li><i class='fa-brands fa-figma'></i>Figma</li>";
                }


                return $lesCompetences . "</ul>";
            }

            $filePath = 'DonneeProjet.csv';
            $lines = [];

            $selected_project = $_GET['pChoose'];

            if (file_exists($filePath)) {
                $lines = file($filePath);

                if ($selected_project == "snake"){
                    $data = explode(";", $lines[1]);
                    $lesCompetences = quelleCompetence($data);
                    $noLigne = 1;
                }

                else if ($selected_project == "duelSnake"){
                    $data = explode(";", $lines[2]);
                    $lesCompetences = quelleCompetence($data);
                    $noLigne = 2;
                }

                else if ($selected_project == "jeuxO"){
                    $data = explode(";", $lines[3]);
                    $lesCompetences = quelleCompetence($data);
                    $noLigne = 3;
                }

                else if ($selected_project == "docker"){
                    $data = explode(";", $lines[4]);
                    $lesCompetences = quelleCompetence($data);
                    $noLigne = 4;
                }

                else if ($selected_project == "baseDonnee"){
                    $data = explode(";", $lines[5]);
                    $lesCompetences = quelleCompetence($data);
                    $noLigne = 5;
                }

                else if ($selected_project == "danone"){
                    $data = explode(";", $lines[6]);
                    $lesCompetences = quelleCompetence($data);
                    $noLigne = 6;
                }

                else if ($selected_project == "lego"){
                    $data = explode(";", $lines[7]);
                    $lesCompetences = quelleCompetence($data);
                    $noLigne = 7;
                }
                
                else if ($selected_project == "spaceInvador"){
                    $data = explode(";", $lines[8]);
                    $lesCompetences = quelleCompetence($data);
                    $noLigne = 8;
                }
            }
            else{
                echo "Fichier non trouvé ou perdu";
            }
        ?>
        <h1 id="titre"><?php echo $data[0] ?></h1>
        <h3>Compétence : <?php echo $data[13] ?></h3>
        <div id="Star">
            <p class="lettreStar">S : <?php echo $data[1]?></p>
            <p class="lettreStar">T : <?php echo $data[2]?></p>
            <p class="lettreStar">A : <?php echo $data[3]?></p>
            <p class="lettreStar">R : <?php echo $data[4]?></p>
        </div>
        <h2>Les langages :</h2>
        <?php echo $lesCompetences?>


        <div id="construction-banner">
            <p>🚧 En travaux 🚧</p>
        </div>
    </body>
</html>


