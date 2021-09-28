<?php
include "conexao.php";

$s1_rec = $_GET['Valorteste'];

$SQL_INSERT = "INSERT INTO sensor_temp (valor_sensor)
 VALUES ('$s1_rec')";
 echo $SQL_INSERT;
$resultado = mysqli_query($conexao,$SQL_INSERT) or die (mysqli_error($resultado));
//header("location: listagem.php");
?>