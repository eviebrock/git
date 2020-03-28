<?php
$emailTo = 'erich.viebrock@gmail.com';
//$toName = 'Erich Viebrock';
$subject = 'Message from erichviebrock.com Portfolio';

if(isset( $_POST['name']))
	$fromName = $_POST['name'];
if(isset( $_POST['email']))
	$emailFrom = $_POST['email'];
if(isset( $_POST['message']))
	$message = $_POST['message'];
	
$headers = 
	'Return-Path: ' . $emailFrom . "\r\n" . 
	'From: ' . $fromName . ' <' . $emailFrom . '>' . "\r\n" . 
	'X-Priority: 3' . "\r\n" . 
	'X-Mailer: PHP ' . phpversion() .  "\r\n" . 
	'Reply-To: ' . $fromName . ' <' . $emailFrom . '>' . "\r\n" .
	'MIME-Version: 1.0' . "\r\n" . 
	'Content-Transfer-Encoding: 8bit' . "\r\n" . 
	'Content-Type: text/plain; charset=UTF-8' . "\r\n";
$params = '-f ' . $emailFrom;
$status = mail($emailTo, $subject, $message, $headers, $params);
echo $status
?>
