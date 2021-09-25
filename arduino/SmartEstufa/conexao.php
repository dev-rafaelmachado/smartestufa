<?php
  $conexao= mysqli_connect("localhost","root","") 
  or die (mysqli_error());
  mysqli_select_db($conexao,"smartestufa") 
  or die(mysqli_error());
    /*
  $CON_CONEXAO = "mysql:host=127.0.0.1:8080;dbname=smartestufa;charset=utf8";
    $CON_USUARIO = 'root';
    $CON_SENHA = '';
    try{
	   $conexao = new PDO($CON_CONEXAO, $CON_USUARIO, $CON_SENHA);
	   echo "Conectado com sucesso";
    }catch (PDOException $erro){
	   echo "erro:";
	   exit;*/
	//}
?>