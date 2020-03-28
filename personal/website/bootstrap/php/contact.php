<?php
if(isset( $_POST['name']))
	$name = $_POST['name'];
if(isset( $_POST['email']))
	$email = $_POST['email'];
if(isset( $_POST['message']))
	$message = $_POST['message'];

$subject = "Message from erichviebrock.com Portfolio";
$content="From: $name \n Email: $email \n Message: $message";
$recipient = "erich.viebrock@gmail.com";
$mailheader = "From: $email \r\n";

mail($recipient, $subject, $content, $mailheader) or die("Error!");

echo "Email sent!";
?>
