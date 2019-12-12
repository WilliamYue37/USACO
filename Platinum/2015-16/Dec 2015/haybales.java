
import java.io.*;
import java.util.*;

public class haybales {

	public static void main(String[] args) throws IOException {
		FastScanner in = new FastScanner(new FileInputStream(new File("haybales.in")));
		PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("haybales.out")));

		int N = in.nextInt(), Q = in.nextInt();
		SegmentTreeSum stSum = new SegmentTreeSum(N);
		SegmentTreeMin stMin = new SegmentTreeMin(N);
		for (int i = 0; i < N; ++i) {
			int num = in.nextInt();
			stSum.increment(i, i, num);
			stMin.increment(i, i, num);
		}
		
		for (int i = 0; i < Q; ++i) {
			char c = in.next().charAt(0);
			if (c == 'M') {
				int A = in.nextInt()-1, B = in.nextInt()-1;
				out.println(stMin.minimum(A, B));
			}
			else if (c == 'P') {
				int A = in.nextInt()-1, B = in.nextInt()-1, C = in.nextInt();
				stMin.increment(A, B, C);
				stSum.increment(A, B, C);
			}
			else {
				int A = in.nextInt()-1, B = in.nextInt()-1;
				out.println(stSum.getSum(A, B));
			}
		}

		out.close();
	}
	
	static class SegmentTreeSum {
		int n;
		int[] lo, hi;
		long[] sum, delta;
		
		public SegmentTreeSum(int n) {
			this.n = n;
			lo = new int[4*n+1];
			hi = new int[4*n+1];
			sum = new long[4*n+1];
			delta = new long[4*n+1];
			
			init(1, 0, n-1);
		}
		
		public void increment(int a, int b, long val) {
			increment(1, a, b, val);
		}
		
		public long getSum(int a, int b) {
			return getSum(1, a, b);
		}
		
		void init(int i, int a, int b) {
			lo[i] = a;
			hi[i] = b;
			
			if (a == b) 
				return;
			
			int m = (a+b)/2;
			init(2*i, a, m);
			init(2*i+1, m+1, b);
		}
		
		void prop(int i) {
			delta[2*i] += delta[i];
			delta[2*i+1] += delta[i];
			delta[i] = 0;
		}
		
		void update(int i) {
			sum[i] = sum[2*i] + delta[2*i] * (hi[2*i] - lo[2*i] + 1) + sum[2*i+1] + delta[2*i+1] * (hi[2*i+1] - lo[2*i+1] + 1);
		}
		
		void increment(int i, int a, int b, long val) {
			if (b < lo[i] || hi[i] < a) 
				return;
			
			if (a <= lo[i] && hi[i] <= b) {
				delta[i] += val;
				return;
			}
			
			prop(i);
			
			increment(2*i, a, b, val);
			increment(2*i+1, a, b, val);
			
			update(i);
		}
		
		long getSum(int i, int a, int b) {
			if (b < lo[i] || hi[i] < a) 
				return 0;
			
			if (a <= lo[i] && hi[i] <= b) {
				return sum[i] + delta[i] * (hi[i] - lo[i] + 1);
			}
			
			prop(i);
			
			long left = getSum(2*i, a, b);
			long right = getSum(2*i+1, a, b);
			
			update(i);
			
			return left + right;
		}
	}
	
	static class SegmentTreeMin {
		int n;
		int[] lo, hi;
		long[] min, delta;
		
		public SegmentTreeMin(int n) {
			this.n = n;
			lo = new int[4*n+1];
			hi = new int[4*n+1];
			min = new long[4*n+1];
			delta = new long[4*n+1];
			
			init(1, 0, n-1);
		}
		
		public void increment(int a, int b, long val) {
			increment(1, a, b, val);
		}
		
		public long minimum(int a, int b) {
			return minimum(1, a, b);
		}
		
		void init(int i, int a, int b) {
			lo[i] = a;
			hi[i] = b;
			
			if (a == b) 
				return;
			
			int m = (a+b)/2;
			init(2*i, a, m);
			init(2*i+1, m+1, b);
		}
		
		void prop(int i) {
			delta[2*i] += delta[i];
			delta[2*i+1] += delta[i];
			delta[i] = 0;
		}
		
		void update(int i) {
			min[i] = Math.min(min[2*i] + delta[2*i], min[2*i+1] + delta[2*i+1]);
		}
		
		void increment(int i, int a, int b, long val) {
			if (b < lo[i] || hi[i] < a) 
				return;
			
			if (a <= lo[i] && hi[i] <= b) {
				delta[i] += val;
				return;
			}
			
			prop(i);
			
			increment(2*i, a, b, val);
			increment(2*i+1, a, b, val);
			
			update(i);
		}
		
		long minimum(int i, int a, int b) {
			if (b < lo[i] || hi[i] < a) 
				return Integer.MAX_VALUE;
			
			if (a <= lo[i] && hi[i] <= b) {
				return min[i] + delta[i];
			}
			
			prop(i);
			
			long minLeft = minimum(2*i, a, b);
			long minRight = minimum(2*i+1, a, b);
			
			update(i);
			
			return Math.min(minLeft, minRight);
		}
	}

	static class FastScanner {
		private InputStream stream;
		private byte[] buf = new byte[1024];
		private int curChar;
		private int numChars;

		public FastScanner(InputStream stream) {
			this.stream = stream;
		}

		int read() {
			if (numChars == -1)
				throw new InputMismatchException();
			if (curChar >= numChars) {
				curChar = 0;
				try {
					numChars = stream.read(buf);
				} catch (IOException e) {
					throw new InputMismatchException();
				}
				if (numChars <= 0)
					return -1;
			}
			return buf[curChar++];
		}

		boolean isSpaceChar(int c) {
			return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
		}

		boolean isEndline(int c) {
			return c == '\n' || c == '\r' || c == -1;
		}

		public int nextInt() {
			return Integer.parseInt(next());
		}

		public long nextLong() {
			return Long.parseLong(next());
		}

		public double nextDouble() {
			return Double.parseDouble(next());
		}

		public String next() {
			int c = read();
			while (isSpaceChar(c))
				c = read();
			StringBuilder res = new StringBuilder();
			do {
				res.appendCodePoint(c);
				c = read();
			} while (!isSpaceChar(c));
			return res.toString();
		}

		public String nextLine() {
			int c = read();
			while (isEndline(c))
				c = read();
			StringBuilder res = new StringBuilder();
			do {
				res.appendCodePoint(c);
				c = read();
			} while (!isEndline(c));
			return res.toString();
		}
	}

}
