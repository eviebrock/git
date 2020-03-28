<?php
if(isset( $_POST['name']))
	$name = $_POST['name'];
if(isset( $_POST['email']))
	$email = $_POST['email'];
if(isset( $_POST['message']))
	$message = $_POST['message'];

$emailto = 'erich.viebrock@gmail.com';
$toname = 'Erich Viebrock';
$emailfrom = $email;
$fromname = $name;
$subject = 'Message from erichviebrock.com Portfolio';
$messagebody = $message;
$headers = 
	'Return-Path: ' . $emailfrom . "\r\n" . 
	'From: ' . $fromname . ' <' . $emailfrom . '>' . "\r\n" . 
	'X-Priority: 3' . "\r\n" . 
	'X-Mailer: PHP ' . phpversion() .  "\r\n" . 
	'Reply-To: ' . $fromname . ' <' . $emailfrom . '>' . "\r\n" .
	'MIME-Version: 1.0' . "\r\n" . 
	'Content-Transfer-Encoding: 8bit' . "\r\n" . 
	'Content-Type: text/plain; charset=UTF-8' . "\r\n";
$params = '-f ' . $emailfrom;
mail($emailto, $subject, $messagebody, $headers, $params);
?>
