


from cloud import *

def breakcloud(cloud):
	"""
	receives 'cloud', an object of type Cloud.
	creates a file with the name 'plain.txt' that stores the current text that is encrypted in the cloud.
	you can use only the Read/Write interfaces of Cloud (do not use its internal variables.)
	"""
	plaintext = ''
	for i in range(cloud.Length()):
		cloud.Write(i,cloud.Read(i))
	for i in range(cloud.Length()):
		plaintext = plaintext + cloud.Read(i)
	with open('plain.txt', mode='wb') as plaintext_file:
		plaintext_file.write(plaintext)
		plaintext_file.close()
	for i in range(len(plaintext)):
		cloud.Write(i,plaintext[i])