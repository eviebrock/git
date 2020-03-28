<?php
$emailTo = 'erich.viebrock@gmail.com';
$subject = 'Message from erichviebrock.com Portfolio';

if(isset( $_POST['name']))
{
	$name = $_POST['name'];
}

if(isset( $_POST['email']))
{
	$emailFrom = $_POST['email'];
}

if(isset( $_POST['message']))
{
	$message = $_POST['message'];
}
	
$headers = 
	'Return-Path: ' . $emailFrom . "\r\n" . 
	'From: ' . $name . ' <' . $emailFrom . '>' . "\r\n" . 
	'X-Priority: 3' . "\r\n" . 
	'X-Mailer: PHP ' . phpversion() .  "\r\n" . 
	'Reply-To: ' . $name . ' <' . $emailFrom . '>' . "\r\n" .
	'MIME-Version: 1.0' . "\r\n" . 
	'Content-Transfer-Encoding: 8bit' . "\r\n" . 
	'Content-Type: text/plain; charset=UTF-8' . "\r\n";
	
$params = '-f ' . $emailFrom;
$status = mail($emailTo, $subject, $message, $headers, $params);

if($status)
{
	echo "Thank you for your message, I will get back to you soon!";
}
else
{
	echo "Email send failed, please try again later.";
}
?>
