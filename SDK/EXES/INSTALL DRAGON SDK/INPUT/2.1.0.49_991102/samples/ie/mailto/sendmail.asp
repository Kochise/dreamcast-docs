<%@ LANGUAGE=JScript %>

<%
  txtTag = "\r\n--\r\nMail sent using Microsoft Dreamcast Test Server.";
%>

<html>

<head>

<title>Sent Mail</title>

</head>

<body bgcolor=lavender>

<%
  var txtFrom = Request.form("from");
  var txtTo   = Request.form("to");
  var txtCC   = Request.form("cc");
  var txtBCC  = Request.form("bcc");
  var txtSubj = Request.form("subject");
  var txtMsg  = Request.form("msg") + txtTag;
%>

<%
  var Mailer = Server.CreateObject("CDONTS.NewMail");
  Mailer.From    = txtFrom;
  Mailer.To      = txtTo;
  Mailer.Cc      = txtCC;
  Mailer.Bcc     = txtBCC;
  Mailer.Subject = txtSubj;
  Mailer.Body    = txtMsg;

  Mailer.Send();
  Mailer = null;
%>

Mail message sent:
<br>
<br>
<table>
  <tr>
    <td style="width:60">From:</td>
    <td style="width:300"><%= txtFrom %>&nbsp;</td>
  </tr>

  <tr>
    <td>To:</td>
    <td><%= txtTo %>&nbsp;</td>
  </tr>

  <tr>
    <td>CC:</td>
    <td><%= txtCC %>&nbsp;</td>
  </tr>

  <tr>
    <td>BCC:</td>
    <td><%= txtBCC %>&nbsp;</td>
  </tr>

  <tr>
    <td>Subject:</td>
    <td><%= txtSubj %>&nbsp;</td>
  </tr>

  <tr>
    <td valign=top colspan=2>
      <textarea readOnly style="background-color:thistle; font-family:Arial; font-size:16; width:530px; height:130px"><%= txtMsg %></textarea>
    </td>
  </tr>
</table>

</body>

</html>
