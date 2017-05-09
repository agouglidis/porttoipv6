<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:template match="/">
  <html>
  
  <style type="text/css">
	h2 { 
		text-decoration: underline; 
		font-family: times
	}
	
	infoFont {
		font-family: times
	}
		
	body {
		background-image: url("logo.gif");
		background-repeat: no-repeat;
		background-position: top right;
		background-attachment: fixed
	}
	
	
  </style>
  
  
  
  
  <body>
  
    <xsl:for-each select="ipv4_metadata/extraInformation">
	
    	<h3></h3>Filename  : <xsl:value-of select="filename"/>
    	<h3></h3>API in use: <xsl:value-of select="api"/>
    	<h2></h2>
    </xsl:for-each>
  

    <table border="0">
      <tr bgcolor="#CCCCFF">
        <th>Line Number</th>
        <th>TypeID</th>
        <th>Type of data</th>
        <th>    Code    </th>
        <th>  Comments  </th>
      </tr>
         
      <xsl:for-each select="ipv4_metadata/information">
      <tr bgcolor="#EDEDF5">
        <td><xsl:value-of select="line" /></td>
        <td><xsl:value-of select="typeid" /></td>
        <td><xsl:value-of select="type" /></td>
	<td><xsl:value-of select="name" /></td>
	<td><xsl:value-of select="comment" /></td>
      </tr>
      </xsl:for-each>
      
    </table>
  </body>
  </html>
</xsl:template>
</xsl:stylesheet>