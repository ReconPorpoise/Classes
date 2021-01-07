n = int(input())

for x in range(n):
	print()
	w1 = input()
	w2 = input()

	w1 = w1.upper()
	w2 = w2.upper()

	if len(w1) < len(w2):
		print(f"{w1} is not a kangaroo word for {w2}")
	else:
		i = len(w1)
		j = 0
		j2 = 0
		kang = ""

		while j < i:
			if w1[ j ] == w2[ j2 ]:
				kang += w1[ j ]
				j += 1
				j2 += 1
				if j2 == len(w2):
					break
			else:
				j += 1
		if kang == w2:
			print(f"{w1} is a kangaroo word for {w2}")
		else:
			print(f"{w1} is not a kangaroo word for {w2}")
