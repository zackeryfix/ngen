

namespace Ngen {
	namespace Data {
		
		class ngen_api DbContext {
		public:
			DbContext(DbQueryProvider* queryProvider) :
				mTables(1), mQueryProvider(queryProvider) {
			
			}
		protected:
			Array<DbTable> mTables
			DbQueryProvider* mQueryProvider;
		};
		
		class ngen_api DbTable {
		public:
			DbTable(DbContext* db, const Type* type) :
				mContext(db), mType(type) {
			}
			
		protected:
			DbContext* mContext;
			const Type* mType;
		};
		
		template<typename... T>
		class ngen_api Table<> {
		
		};
		
		template<typename... T>
		class ngen_api Table {
		public:
			typedef Tuple<T...> Row;
			typedef Table<T...> TSelf;
			
			Table(uwhole size = 1) : mRows(size) {
			}
			
			Table(const Row& empty) : mRows(1) {
				 mRows.Add(empty);
			}
			
			Table(const Array<Row>& copy, bool readOnly = false) : mRows(copy, readOnly) {
			}
			
			Table(const TSelf& copy, bool readOnly = false) : mRows(copy.mRows, readOnly) {
			}
			
			template<typename U>
			U& At(uwhole row, const uwhole col) {
				return get<col>(mRows[row]);
			}
			
			TSelf& Add(const TRow& row) {
				mRows.Add(row);
			}
			
			uwhole Length() const {
				return mRows.Length();
			}
			
			
			
			template<typename... TJoin>
			Table<T..., TJoin...>& Join(const Table<TJoin...>& table, NonVoidStaticDelegate<bool, const TRow&, const Tuple<TJoin...>&>::TFunction where) const {
				using TResult = Table<T..., TJoin...>;
				using TResRow = TResult::Row;
				
				TResult result = TResult(0);
				for(uwhole i = 0; i < mRows.Length() && i < table.mRows.Length(); ++i) {
					if(where(mRows[i], table.mRows[i])) {
						TResRow row;
						const uwhole si = sizeof...(T);
						const uwhole ze = sizeof...(TJoin);
						uwhole s = 0
						for(uwhole li = 0; li < si; ++li) {
							get<s>(row) = get<li>(mRows[i]);
							s++;
						}
						
						for(uwhole ri = 0; ri < ze; ++ri) {
							get<s>(row) = get<ri>(table.mRows[i]);
							s++;
						}
						
						result.Add(row);
					}
				}
				
				return result;
			}
			
		protected:
			Array<Row> mRows;
		};
		
		template<typename T, typename... TTail>
		class ngen_api Tuple : Tuple<TTaill...> {
		public:
			typedef Tuple<T, TTail...> TSelf;
			
			Tuple(T value, TTail... tail) : 
				Tuple<TTail...>(tail), mValue(value) {
			}
	
			T Value;
		};

		template<typename T, typename... TTail>
		struct tuple_iter<0, Tuple<T, TTail> > : Tuple<TTaill...> {
			typedef T type;
		};
		
		template<uwhole I, typename T, typename... TTail>
		struct tuple_iter<I, Tuple<T, TTail> > : Tuple<TTaill...> {
			typedef typename tuple_iter<I - 1, Tuple<TTail...> >::type type;
		};
		
		template<uwhole I, typename... T>
  	typename tuple_iter<0, Tuple<T...>>::type&>::type get(tuple<T...>& e) {
			return e.Value;
		}

		template<uwhole I, typename T, typename... T>
   typename tuple_iter<I, Tuple<T, T...>>::type&>::type get(Tuple<T, T...>& e) {
			Tuple<T...>& tmp = e;
			return get<I - 1>(tmp);
		}
}