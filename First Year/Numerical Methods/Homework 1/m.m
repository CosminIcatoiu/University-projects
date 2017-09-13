function [p k]=m(tip)

p=0;

if(tip == 1)

	for i= 16:256
		[X t]=preprocess("dataset","RGB",i);
		w=learn(X,t);
		pr=evaluate("testset",w,"RGB",i);		
		if(pr>p)
			p=pr;
			k=i;
		endif
	endfor
endif
endfunction
